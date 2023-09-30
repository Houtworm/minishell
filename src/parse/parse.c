/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/30 07:38:31 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_parsecmds(t_shell *shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell->forks[forknumber].cmds[cmdnumber].envp = shell->envp;
	shell->forks[forknumber].cmds[cmdnumber].debug = shell->debug;
	shell->forks[forknumber].cmds[cmdnumber].forkamount = shell->forkamount;
	shell->forks[forknumber].cmds[cmdnumber].prio = ft_priority(shell->forks[forknumber].cmds, cmdnumber); //0;
	ft_parsealiases(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsevariable(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_executepriority(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseredirection(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseglobs(&shell->forks[forknumber].cmds[cmdnumber]); //should be moved to ft_parseline()
	paths = ft_getpaths(shell->envp, 1);
	shell->forks[forknumber].cmds[cmdnumber].arguments = split_not_quote(shell->forks[forknumber].cmds[cmdnumber].pipeline, ' ');
	shell->forks[forknumber].cmds[cmdnumber].arguments = ft_checkarg(shell->forks[forknumber].cmds[cmdnumber].arguments, 0);
	if (!shell->forks[forknumber].cmds[cmdnumber].arguments[0])
	{
		shell->stop = 1;
		ft_frearr(paths);
		return (shell);
	}
	shell->forks[forknumber].cmds[cmdnumber].cmdamount = shell->forks[forknumber].cmdamount;
	shell->forks[forknumber].cmds[cmdnumber].absolute = ft_abspathcmd(paths, shell->forks[forknumber].cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
	return (shell);
}

char	*ft_parseoldline(char *line, t_shell *shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*rest;

	begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] && (line[i] != '!' || line[i + 1] != '!'))
		{
			if (line[i] == '\'')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\'')
				{
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			begin[j] = line[i];
			i++;
			j++;
		}
		if (line[i] == '!' && line[i + 1] == '!')
		{
			if (!shell->oldline[0])
				return (NULL);
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (line[i])
			{
				rest[j] = line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free (line);
			line = ft_vastrjoin(3, begin, shell->oldline, rest);
			i = 0;
		}
	}
	ft_vafree(2, begin, rest);
	return (line);
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
	if (ft_parseoldline(line, shell) == NULL)
		return (127);
	/*free(shell->oldline);*/
	shell->oldline = ft_strdup(line);
	line = ft_parsehashtag(line);
	if (line[0] == '\0')
		return (1);
	if (ft_checksyntax(shell, line))
		return (2);
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
	return (0);
}
