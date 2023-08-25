/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/25 03:01:15 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_testfillfakestruct(t_shell *shell, char *line)
{

	shell->line = line;
	char	**paths;

	paths = ft_getpaths(shell->envp, 1); // This should probably be done somewhere else?
	shell->forkamount = 1;
	shell->forks = ft_calloc(10 * sizeof(t_forks), 1);
	shell->forks->cmdamount = 1;
	shell->forks->cmds = ft_calloc(10 * sizeof(t_cmds), 1);
	shell->forks[0].cmds[0].envp = shell->envp;
	shell->forks[0].cmds[0].arguments = ft_split(line, ' ');
	shell->forks[0].cmds[0].absolute = ft_abspathcmd(paths, shell->forks[0].cmds[0].arguments[0]);
	shell->forks[0].cmds[0].detatch = 0;
	shell->forks[0].cmds[0].condition = 0;
	shell->forks[0].cmds[0].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	shell->forks[0].cmds[0].redirect[0].fd_in = 0;
	shell->forks[0].cmds[0].redirect[0].fd_out = 1;
	shell->forks[0].cmds[0].redirect[0].trc_apd = 1;
	ft_frearr(paths);
	return (shell);
}

int	*ft_parseline(char *line, t_shell *shell)
{
	shell = ft_testfillfakestruct(shell, line); 
	// This will fill the struct with fake variables, 
	// so if you are testing something just comment out the line in this function,
	// that way you use the variables of your parsing and not the fake ones put in place by the function.
	// if it at least doesn't segfault  the application or mess with other outputs you can leave it be and slowly add all the parsing till you're done :)

/*yuka working
	char	**arr;

	if (!check_quote_closed(line))
		printf("num of str = %d\n", count_str(line, '|'));
	shell->forks = ft_forks_strct(line, shell);
	printf("end of testing\n");
	exit(0);
//*/
	return (SUCCESS);
}
