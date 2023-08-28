/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   pipe.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/28 13:26:01 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/28 13:56:45 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	ft_parsepipe(char *line, t_shell shell)
{
	char	**tmp;

	shell.forkamount = 0;
	shell.line = ft_strdup(line);
	shell.forks = ft_calloc(1000 * sizeof(t_forks), 1);
	tmp = ft_split(line, '|');
	while (tmp[shell.forkamount])
	{
		shell.forks[shell.forkamount].pipeline = ft_strdup(tmp[shell.forkamount]);
		shell.forkamount++;
	}
	return (shell);
}
