/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 04:57:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/08 09:38:59 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_errorexit(char *reason, char *cmd, int code)
{
	ft_semwait("/tmp/minishellprintsem");
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	ft_semfree("/tmp/minishellprintsem");
	exit (code);
}

int	ft_moderrorexit(char *reason, char *cmd, char *cmd2, int code)
{
	ft_semwait("/tmp/minishellprintsem");
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd2, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	ft_semfree("/tmp/minishellprintsem");
	exit (code);
}

int	ft_errorreturn(char *reason, char *cmd, int code)
{
	ft_semwait("/tmp/minishellprintsem");
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	ft_semfree("/tmp/minishellprintsem");
	return (code);
}

int	ft_moderrorreturn(char *reason, char *cmd, char *cmd2, int code)
{
	ft_semwait("/tmp/minishellprintsem");
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd2, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	ft_semfree("/tmp/minishellprintsem");
	return (code);
}
