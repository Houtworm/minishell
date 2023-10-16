/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/17 01:17:06 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_removequotes(char **args)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	char	quote;

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
		{
			while (args[i][j] && args[i][j] != '\'' && args[i][j] != '\"')
			{
				new[i][k] = args[i][j];
				j++;
				k++;
			}
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				quote = args[i][j];
				j++;
				while (args[i][j] && args[i][j] != quote)
				{
					new[i][k] = args[i][j];
					j++;
					k++;
				}
				j++;
			}
		}
		new[i][k] = '\0';
		i++;
	}
	ft_frearr(args);
	new[i] = NULL;
	new[i + 1] = NULL;
	return (new);
}

char	**ft_splitcmd(char *cmd)
{
	char	**arguments;
	int		icmd;
	int		argument;
	int		iarg;
	char	quote;

	icmd = 0;
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
	arguments = ft_calloc(argument, 8);
	icmd = 0;
	argument = 0;
	while (cmd[icmd] == ' ')
		icmd++;
	while (cmd[icmd])
	{
		arguments[argument] = ft_calloc(1000, 8);
		iarg = 0;
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'' || cmd[icmd] == '\"')
			{
				arguments[argument][iarg] = cmd[icmd];
				quote = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != quote)
				{
					arguments[argument][iarg] = cmd[icmd];
					iarg++;
					icmd++;
				}
			}
			if (cmd[icmd])
			{
				arguments[argument][iarg] = cmd[icmd];
				iarg++;
				icmd++;
			}
		}
		arguments[argument][iarg] = '\0';
		while (cmd[icmd] == ' ')
			icmd++;
		argument++;
	}
	arguments[argument] = NULL;
	return (arguments);
}

t_shell *ft_parsecommands(t_shell *msh, int forknumber, int cmdnumber)
{
	char	**paths;

	msh->frk[forknumber].cmd[cmdnumber].debug = msh->debug;
	msh->frk[forknumber].cmd[cmdnumber].forkamount = msh->forkamount;
	msh->frk[forknumber].cmd[cmdnumber].prio = ft_priority(msh->frk[forknumber].cmd, cmdnumber);
	ft_parsealiases(&msh->frk[forknumber].cmd[cmdnumber], *msh);
	ft_parsevariable(&msh->frk[forknumber].cmd[cmdnumber], *msh);
	ft_parsetilde(&msh->frk[forknumber].cmd[cmdnumber], *msh);
	if (ft_parseredirection(&msh->frk[forknumber].cmd[cmdnumber]))
	{
		msh->stop = 2;
		return (msh);
	}
	ft_executepriority(&msh->frk[forknumber].cmd[cmdnumber], msh->envp);
	ft_parseglobs(&msh->frk[forknumber].cmd[cmdnumber], msh->envp);
	paths = ft_splitcmd(msh->frk[forknumber].cmd[cmdnumber].pipeline);
	msh->frk[forknumber].cmd[cmdnumber].arg = ft_removequotes(paths);
	if (!msh->frk[forknumber].cmd[cmdnumber].arg[0])
	{
		msh->stop = 1;
		return (msh);
	}
	msh->frk[forknumber].cmd[cmdnumber].cmdamount = msh->frk[forknumber].cmdamount;
	paths = ft_getpaths(msh->envp, 1);
	if (!paths)
		msh->frk[forknumber].cmd[cmdnumber].absolute = ft_strdup(msh->frk[forknumber].cmd[cmdnumber].arg[0]);
	else
	{
		msh->frk[forknumber].cmd[cmdnumber].absolute = ft_abspathcmd(paths, msh->frk[forknumber].cmd[cmdnumber].arg[0]);
		ft_frearr(paths);
	}
	return (msh);
}

int	ft_parseline(char *line, t_shell *msh)
{
	int	forknumber;

	free(msh->line);
	msh->line = ft_strdup(line);
	if (!ft_parseoldline(msh))
		return (127);
	if (ft_startsyntax(msh))
		return (2);
	while (check_quote_closed(msh))
	{
		ft_closeline(msh);
		ft_completeline(msh, 0);
	}
	ft_parsehashtag(msh);
	if (msh->line[0] == '\0')
		return (1);
	if (ft_checksyntax(msh))
		return (2);
	ft_parsepipe(msh);
	if (msh->debug)
		ft_printshell(*msh);
	forknumber = 0;
	while (msh->forkamount > forknumber)
	{
		ft_parseendcondition(msh, forknumber);
		ft_parseheredoc(msh, forknumber);
		if (msh->debug)
			ft_printforks(msh->frk[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
