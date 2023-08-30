/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/08/30 18:20:05 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	ft_parsepipe(char *line, t_shell shell)
{
	char	**tmp;

	shell.forkamount = 0;
	shell.line = ft_strdup(line);
	shell.forks = ft_calloc(1000 * sizeof(t_forks), 1);
	tmp = split_not_quote(line, '|');
	while (tmp[shell.forkamount])
	{
		shell.forks[shell.forkamount].pipeline = ft_strdup(tmp[shell.forkamount]);
		shell.forkamount++;
	}
	ft_frearr(tmp);
	return (shell);
}
