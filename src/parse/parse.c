/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/23 18:15:02 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_parsecmds(t_shell *msh, int f, int c, char **path)
{
	msh->frk[f].cmd[c].debug = msh->debug;
	msh->frk[f].cmd[c].forks = msh->forks;
	msh->frk[f].cmd[c].prio = ft_priority(msh->frk[f].cmd, c, 0, 0);
	ft_parsealiases(&msh->frk[f].cmd[c], *msh);
	msh->frk[f].cmd[c].line = ft_parsevar(msh->frk[f].cmd[c].line, *msh, 1);
	msh->frk[f].cmd[c].line = ft_parsetilde(msh->frk[f].cmd[c].line, *msh);
	if (ft_parseoutputfiles(&msh->frk[f].cmd[c]))
		return (2);
	ft_executepriority(&msh->frk[f].cmd[c], msh->envp, msh->sysfile);
	ft_parseglobs(&msh->frk[f].cmd[c], msh->envp);
	path = ft_splitcmd(msh->frk[f].cmd[c].line);
	msh->frk[f].cmd[c].arg = ft_removequotes(path);
	if (!msh->frk[f].cmd[c].arg[0])
		return (1);
	msh->frk[f].cmd[c].cmds = msh->frk[f].cmds;
	path = ft_getpaths(msh->envp, 1);
	if (!path)
		msh->frk[f].cmd[c].abs = ft_strdup(msh->frk[f].cmd[c].arg[0]);
	else
	{
		msh->frk[f].cmd[c].abs = ft_abspathcmd(path, msh->frk[f].cmd[c].arg[0]);
		ft_frearr(path);
	}
	return (0);
}

int	ft_parseline(char *line, t_shell *msh, int forknumber)
{
	free(msh->line);
	msh->line = ft_strdup(line);
	if (!ft_parseoldline(msh))
		return (ft_errorret("command not found", "!!", 127));
	if (ft_startsyntax(msh, 0))
		return (2);
	ft_close_completeline(msh);
	ft_parsehashtag(msh);
	if (msh->line[0] == '\0')
		return (4);
	if (ft_checksyntax(msh))
		return (2);
	ft_parsepipe(msh);
	if (msh->debug)
		ft_printshell(*msh);
	while (msh->forks > forknumber)
	{
		ft_parseendcondition(msh, forknumber, 0, 0);
		if (ft_parseinputfiles(msh, forknumber))
			return (1);
		if (msh->debug)
			ft_printforks(msh->frk[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
