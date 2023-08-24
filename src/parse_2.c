/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/24 14:59:26 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



/*
cmd1: cat '< file1 | grep a' | wc -l > file2 > file3
command[1] cat < file1
command[2] grep a 
command[3] wc -l > file2 > file3	
(for char **argument, cut out the redirection part = only 'cat' or 'wc\n -l')
*/

void	ft_strct_per_cmd(char **cmd, t_shell *shell)
{
	t_exec	*commands;
	char	**paths;
	int		i;

	commands = ft_calloc(count_str(shell->line, '|') + 1, sizeof(t_exec));
	if (!commands)
		return ;	//ft_error()?;
	i = 0;
	paths = ft_getpaths(shell->envp, 1);
	while (cmd[i])
	{
		// before split cmd by space, split cmd by &&, ||, (+ &)?
		// then ft_check_redirect needs to happen -> ft_substr take cmd before < > << >>
		// 
		ft_check_redirect(commands[i], cmd[i]);
		commands[i].arguments = split_not_quote(cmd[i], ' ');
		commands[i].absolute = ft_abspathcmd(paths, commands[i].arguments[0]);
		printf("%s\n", commands[i].absolute);
		i++;
	}
	shell->forks->commands = commands;
	ft_frearr(paths);
	// ft_check_redirect(shell->forks->commands, i);
}
