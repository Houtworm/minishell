/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/09 02:11:45 by houtworm     \___)=(___/                 */
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
				/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
				j++;
				k++;
			}
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				quote = args[i][j];
				/*printf("skipping quote %c\n", quote);*/
				j++;
				while (args[i][j] && args[i][j] != quote)
				{
					new[i][k] = args[i][j];
					/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
					j++;
					k++;
				}
				/*printf("closing quote %c\n", quote);*/
				j++;
			}
		}
		new[i][k] = '\0';
		/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
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
	int		arg;
	int		iarg;
	char	quote;

	icmd = 0;
	arg = 1;
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
		arg++;
	}
	arguments = ft_calloc(arg, 8);
	icmd = 0;
	arg = 0;
	while (cmd[icmd] == ' ')
		icmd++;
	while (cmd[icmd])
	{
		arguments[arg] = ft_calloc(1000, 8);
		iarg = 0;
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'' || cmd[icmd] == '\"')
			{
				arguments[arg][iarg] = cmd[icmd];
				quote = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != quote)
				{
					arguments[arg][iarg] = cmd[icmd];
					iarg++;
					icmd++;
				}
			}
			if (cmd[icmd])
			{
				arguments[arg][iarg] = cmd[icmd];
				iarg++;
				icmd++;
			}
		}
		arguments[arg][iarg] = '\0';
		while (cmd[icmd] == ' ')
			icmd++;
		arg++;
	}
	arguments[arg] = NULL;
	return (arguments);
}

t_shell *ft_parsecmds(t_shell *shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell->forks[forknumber].cmds[cmdnumber].debug = shell->debug;
	shell->forks[forknumber].cmds[cmdnumber].forkamount = shell->forkamount;
	shell->forks[forknumber].cmds[cmdnumber].prio = ft_priority(shell->forks[forknumber].cmds, cmdnumber); //0;
	ft_parsealiases(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsevariable(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsetilde(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_executepriority(&shell->forks[forknumber].cmds[cmdnumber], shell->envp);
	ft_parseredirection(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseglobs(&shell->forks[forknumber].cmds[cmdnumber], shell->envp); //should be moved to ft_parseline()
	paths = ft_splitcmd(shell->forks[forknumber].cmds[cmdnumber].pipeline);
	shell->forks[forknumber].cmds[cmdnumber].arguments = ft_removequotes(paths);
	if (!shell->forks[forknumber].cmds[cmdnumber].arguments[0])
	{
		shell->stop = 1;
		return (shell);
	}
	shell->forks[forknumber].cmds[cmdnumber].cmdamount = shell->forks[forknumber].cmdamount;
	paths = ft_getpaths(shell->envp, 1);
	shell->forks[forknumber].cmds[cmdnumber].absolute = ft_abspathcmd(paths, shell->forks[forknumber].cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
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
			ft_printforks(shell->forks[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
