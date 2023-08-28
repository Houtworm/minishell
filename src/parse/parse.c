/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/28 12:27:54 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_setcmddefaults(t_shell *shell, int i, int j)
{
	shell->forks[i].cmds[j].envp = shell->envp;
	shell->forks[i].cmds[j].detatch = 0;
	shell->forks[i].cmds[j].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	shell->forks[i].cmds[j].redirect[0].fd_in = 0;
	shell->forks[i].cmds[j].redirect[0].fd_out = 1;
}

void	ft_finalparsing(t_forks *forks, int i, int j)
{
	char	**paths;

	paths = ft_getpaths(forks->cmds[0].envp, 1);
	forks[i].cmds[j].arguments = ft_split(forks[i].cmds[j].pipeline, ' ');
	forks[i].cmds[j].absolute = ft_abspathcmd(paths, forks[i].cmds[j].arguments[0]);
	ft_frearr(paths);
}

t_shell	ft_parseline(char *line, t_shell shell)
{
	int	i;
	int	j;
	// if (check_quote_closed(line))
	shell.forks = ft_parsepipe(line, &shell);
	ft_printshell(shell);
	/*shell->forks = ft_parsespchr(shell->forks, shell);*/
	i = 0;
	while (shell.forkamount > i) // forks loop should set the cmds.pipeline and set cmds.conditions
	{
		shell.forks[i] = ft_parseendcondition(shell.forks[i]);
		ft_printforks(shell.forks[i], i);
		j = 0;
		while (shell.forks[i].cmdamount > j) // cmds loop should expand, handle redirections and split the pipeline into the arguments
		{
			ft_setcmddefaults(&shell, i, j);
			ft_parsevariable(shell.forks[i].cmds[j]); //expanding pipeline
			/*ft_parsewildcard(shell.forks[i].cmds[j]); //expanding pipeline*/
			ft_finalparsing(shell.forks, i, j);
			ft_printcmds(shell.forks[i].cmds[j], j);
			j++;
		}
		i++;
	}
	// if (!check_quote_closed(line)) // should probably be done at the beginning since you can't parse a incomplete line.
	return (shell);
}
