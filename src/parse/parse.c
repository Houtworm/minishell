/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/26 13:17:02 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_testfillfakestruct(t_shell *shell, char *line)
{

	shell->line = line;
	char	**paths;

	paths = ft_getpaths(shell->envp, 1); // This should probably be done somewhere else?
	shell->forkamount = 1; //number of fork structs
	shell->forks = ft_calloc(10 * sizeof(t_forks), 1); //temp calloc
	shell->forks->cmdamount = 1; //number of command structs
	shell->forks->cmds = ft_calloc(10 * sizeof(t_cmds), 1); //temp calloc
	shell->forks[0].cmds[0].envp = &shell->envp; //copy over envp (should be done to every single command struct)
	shell->forks[0].cmds[0].arguments = ft_split(line, ' '); // can be removed as soon as you populate the command struct with the arguments.
	shell->forks[0].cmds[0].absolute = ft_abspathcmd(paths, shell->forks[0].cmds[0].arguments[0]); //can be removed after arguments and absolute are handled by the parser.
	shell->forks[0].cmds[0].detatch = 0; // wether to detach the process (&)
	shell->forks[0].cmds[0].condition = 0; // && || or no condition.
	shell->forks[0].cmds[0].redirect = ft_calloc(10 * sizeof(t_redirect), 1); //temp calloc
	shell->forks[0].cmds[0].redirect[0].fd_in = 0; // in fd make it -1 for heredoc
	shell->forks[0].cmds[0].redirect[0].fd_out = 1; // out fd, 
	shell->forks[0].cmds[0].redirect[0].trc_apd = 1; //trunc append. This is probably completely handled by you, since you open the files and just pass the fd. so it probably doesn't have to be passed to the executioner.
	ft_frearr(paths); //free the temporary paths.
	return (shell);
}

int	*ft_parseline(char *line, t_shell *shell)
{
	// shell = ft_testfillfakestruct(shell, line); 
	
	// This will fill the struct with fake variables, 
	// so if you are testing something just comment out the line in this function,
	// that way you use the variables of your parsing and not the fake ones put in place by the function.
	// if it at least doesn't segfault  the application or mess with other outputs you can leave it be and slowly add all the parsing till you're done :)

//yuka working

	if (!check_quote_closed(line))
		printf("num of str = %d\n", count_str(line, '|'));
	shell->forks = ft_parsepipe(line, shell);
	// printf("split by pip %s\n", shell->forks[0].pipeline);
	// printf("split by pip %s\n", shell->forks[1].pipeline);
	// printf("split by pip %s\n", shell->forks[2].pipeline);
	
	shell->forks = ft_parsespchr(shell->forks, shell);
	// printf("split by spchr %s\n", shell->forks[0].cmds[0].absolute);
	// printf("split by spchr %s\n", shell->forks[1].cmds[0].absolute);
	// printf("split by spchr %s\n", shell->forks[1].cmds[1].absolute);
	// printf("split by spchr %s\n", shell->forks[0].cmds[2].absolute);

	printf("end of testing\n");
	/*exit(0);*/
//*/
	return (0);
}
