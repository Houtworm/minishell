/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/16 10:40:03 by houtworm     \___)=(___/                 */
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

t_shell *ft_parsecommands(t_shell *shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell->frk[forknumber].cmd[cmdnumber].debug = shell->debug;
	shell->frk[forknumber].cmd[cmdnumber].forkamount = shell->forkamount;
	shell->frk[forknumber].cmd[cmdnumber].prio = ft_priority(shell->frk[forknumber].cmd, cmdnumber);
	ft_parsealiases(&shell->frk[forknumber].cmd[cmdnumber], *shell);
	ft_parsevariable(&shell->frk[forknumber].cmd[cmdnumber], *shell);
	ft_parsetilde(&shell->frk[forknumber].cmd[cmdnumber], *shell);
	if (ft_parseredirection(&shell->frk[forknumber].cmd[cmdnumber]))
	{
		shell->stop = 2;
		return (shell);
	}
	ft_executepriority(&shell->frk[forknumber].cmd[cmdnumber], shell->envp);
	ft_parseglobs(&shell->frk[forknumber].cmd[cmdnumber], shell->envp);
	paths = ft_splitcmd(shell->frk[forknumber].cmd[cmdnumber].pipeline);
	shell->frk[forknumber].cmd[cmdnumber].arg = ft_removequotes(paths);
	if (!shell->frk[forknumber].cmd[cmdnumber].arg[0])
	{
		shell->stop = 1;
		return (shell);
	}
	shell->frk[forknumber].cmd[cmdnumber].cmdamount = shell->frk[forknumber].cmdamount;
	paths = ft_getpaths(shell->envp, 1);
	if (!paths)
		shell->frk[forknumber].cmd[cmdnumber].absolute = ft_strdup(shell->frk[forknumber].cmd[cmdnumber].arg[0]);
	else
	{
		shell->frk[forknumber].cmd[cmdnumber].absolute = ft_abspathcmd(paths, shell->frk[forknumber].cmd[cmdnumber].arg[0]);
		ft_frearr(paths);
	}
	return (shell);
}

int	ft_parseline(char *line, t_shell *shell)
{
	int	forknumber;

	free(shell->line);
	shell->line = ft_strdup(line);
	if (!ft_parseoldline(shell))
		return (127);
	if (ft_startsyntax(shell))
		return (2);
	while (check_quote_closed(shell))
	{
		ft_closeline(shell);
		ft_completeline(shell, 0);
	}
	ft_parsehashtag(shell);
	if (shell->line[0] == '\0')
		return (1);
	if (ft_checksyntax(shell))
		return (2);
	ft_parsepipe(shell);
	if (shell->debug)
		ft_printshell(*shell);
	forknumber = 0;
	while (shell->forkamount > forknumber)
	{
		ft_parseendcondition(shell, forknumber);
		ft_parseheredoc(shell, forknumber);
		if (shell->debug)
			ft_printforks(shell->frk[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
