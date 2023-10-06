/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/06 18:44:08 by yitoh         ########   odam.nl         */
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

	icmd = 0;
	arg = 1;
	while (cmd[icmd])
	{
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'')
			{
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\'')
					icmd++;
			}
			if (cmd[icmd] == '\"')
			{
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\"')
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
			if (cmd[icmd] == '\'')
			{
				arguments[arg][iarg] = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\'')
				{
					arguments[arg][iarg] = cmd[icmd];
					iarg++;
					icmd++;
				}
			}
			else if (cmd[icmd] == '\"')
			{
				arguments[arg][iarg] = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\"')
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

	if (ft_startsyntax(shell, line))
		return (2);
	/*line = ft_closeline(line);*/
	/*line = ft_completeline(line, 0);*/
	while (check_quote_closed(line))
	{
		line = ft_closeline(line);
		line = ft_completeline(line, 0);
	}
	line = ft_parseoldline(line, shell);
	if (!line)
		return (127);
	//free(shell->oldline);
	shell->oldline = ft_strdup(line);
	line = ft_parsehashtag(shell->oldline);
	if (line[0] == '\0')
	{
		free(line);
		return (1);
	}
	if (ft_checksyntax(shell, line))
	{
		free(line);
		return (2);
	}
	*shell = ft_parsepipe(line, *shell);
	if (shell->debug)
		ft_printshell(*shell);
	forknumber = 0;
	while (shell->forkamount > forknumber)
	{
		shell->forks[forknumber] = ft_parseendcondition(shell->forks[forknumber]);
		shell->forks[forknumber] = ft_parseheredoc(shell->forks[forknumber], shell->forks[forknumber].cmdamount);
		if (shell->debug)
			ft_printforks(shell->forks[forknumber], forknumber);
		forknumber++;
	}
	free(line);
	return (0);
}
