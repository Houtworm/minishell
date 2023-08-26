/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 04:57:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/08/26 08:16:42 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_errorexit(char *reason, char *cmd, int code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	if (code)
		exit (code);
	else
		return (1);
}
