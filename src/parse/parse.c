/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/20 16:16:18 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_cpnonquote(char *args, char *new, int *j, int *k)
{
	char	quote;

	while (args[*j] && args[*j] != '\'' && args[*j] != '\"')
	{
		new[*k] = args[*j];
		(*j)++;
		(*k)++;
	}
	if (args[*j] == '\'' || args[*j] == '\"')
	{
		quote = args[*j];
		(*j)++;
		while (args[*j] && args[*j] != quote)
		{
			new[*k] = args[*j];
			(*j)++;
			(*k)++;
		}
		(*j)++;
	}
	return (new);
}

char	**ft_removequotes(char **args)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (args[i])
		i++;
	new = ft_calloc(i + 2, 8);
	i = 0;
	while (args[i])
	{
		new[i] = ft_calloc(1000, 8);
		j = 0;
		k = 0;
		while (args[i][j])
			new[i] = ft_cpnonquote(args[i], new[i], &j, &k);
		new[i][k] = '\0';
		i++;
	}
	ft_frearr(args);
	new[i] = NULL;
	new[i + 1] = NULL;
	return (new);
}

int	ft_countargs(char *cmd, int icmd)
{
	int		argument;
	char	quote;

	argument = 1;
	while (cmd[icmd])
	{
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'' || cmd[icmd] == '\"')
			{
				quote = cmd[icmd];
				icmd++;
				while (cmd[icmd] && cmd[icmd] != quote)
					icmd++;
			}
			if (cmd[icmd])
				icmd++;
		}
		while (cmd[icmd] == ' ')
			icmd++;
		argument++;
	}
	return (argument);
}

char	*ft_cpwithquote(char *cmd, char *arg, int *icmd, int *iarg)
{
	char	quote;

	if (cmd[*icmd] == '\'' || cmd[*icmd] == '\"')
	{
		arg[*iarg] = cmd[*icmd];
		quote = cmd[*icmd];
		(*iarg)++;
		(*icmd)++;
		while (cmd[*icmd] && cmd[*icmd] != quote)
		{
			arg[*iarg] = cmd[*icmd];
			(*iarg)++;
			(*icmd)++;
		}
	}
	if (cmd[*icmd])
	{
		arg[*iarg] = cmd[*icmd];
		(*iarg)++;
		(*icmd)++;
	}
	return (arg);
}

char	**ft_splitcmd(char *cmd)
{
	char	**arguments;
	int		icmd;
	int		arg;
	int		iarg;

	arguments = ft_calloc(ft_countargs(cmd, 0), 8);
	icmd = 0;
	arg = 0;
	while (cmd[icmd] == ' ')
		icmd++;
	while (cmd[icmd])
	{
		arguments[arg] = ft_calloc(1000, 8);
		iarg = 0;
		while (cmd[icmd] && cmd[icmd] != ' ')
			arguments[arg] = ft_cpwithquote(cmd, arguments[arg], &icmd, &iarg);
		arguments[arg][iarg] = '\0';
		while (cmd[icmd] == ' ')
			icmd++;
		arg++;
	}
	arguments[arg] = NULL;
	return (arguments);
}

int	ft_parsecommands(t_shell *msh, int f, int c)
{
	char	**paths;

	msh->frk[f].cmd[c].debug = msh->debug;
	msh->frk[f].cmd[c].forks = msh->forks;
	msh->frk[f].cmd[c].prio = ft_priority(msh->frk[f].cmd, c, 0, 0);
	ft_parsealiases(&msh->frk[f].cmd[c], *msh);
	msh->frk[f].cmd[c].line = ft_parsevariable(msh->frk[f].cmd[c].line, *msh, 1);
	msh->frk[f].cmd[c].line = ft_parsetilde(msh->frk[f].cmd[c].line, *msh);
	if (ft_parseoutputfiles(&msh->frk[f].cmd[c]))
		return (2);
	ft_executepriority(&msh->frk[f].cmd[c], msh->envp, msh->sysfile);
	ft_parseglobs(&msh->frk[f].cmd[c], msh->envp);
	paths = ft_splitcmd(msh->frk[f].cmd[c].line);
	msh->frk[f].cmd[c].arg = ft_removequotes(paths);
	if (!msh->frk[f].cmd[c].arg[0])
		return (1);
	msh->frk[f].cmd[c].cmds = msh->frk[f].cmds;
	paths = ft_getpaths(msh->envp, 1);
	if (!paths)
		msh->frk[f].cmd[c].absolute = ft_strdup(msh->frk[f].cmd[c].arg[0]);
	else
	{
		msh->frk[f].cmd[c].absolute = ft_abspathcmd(paths, msh->frk[f].cmd[c].arg[0]);
		ft_frearr(paths);
	}
	return (0);
}

//if we remove the printing, it will be normed
int	ft_parseline(char *line, t_shell *msh, int forknumber)
{
	free(msh->line);
	msh->line = ft_strdup(line);
	if (!ft_parseoldline(msh))
		return (127);
	if (ft_startsyntax(msh))
		return (2);
	while (check_quote_closed(msh))
	{
		ft_closeline(msh, check_quote_closed(msh), NULL);
		ft_completeline(msh, 0, NULL);
	}
	ft_parsehashtag(msh);
	if (msh->line[0] == '\0')
		return (1);
	if (ft_checksyntax(msh))
		return (2);
	ft_parsepipe(msh);
	if (msh->debug)
		ft_printshell(*msh);
	while (msh->forks > forknumber)
	{
		ft_parseendcondition(msh, forknumber, 0, 0);
		if (ft_parseinputfiles(msh, forknumber))
			return (3);
		if (msh->debug)
			ft_printforks(msh->frk[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
