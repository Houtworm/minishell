/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 04:57:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/13 03:32:21 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_errorexit(char *reason, char *cmd, int code)
{
	char	*str;

	str = ft_vastrjoin(4, "msh: ", cmd, ": ", reason);
	ft_semwait("/tmp/minishellprintsem");
	ft_putendl_fd(str, 2);
	ft_semfree("/tmp/minishellprintsem");
	free(str);
	exit (code);
}

int	ft_moderrorexit(char *reason, char *cmd, char *cmd2, int code)
{
	char	*str;

	str = ft_vastrjoin(6, "msh: ", cmd, ": ", cmd2, ": ", reason);
	ft_semwait("/tmp/minishellprintsem");
	ft_putendl_fd(str, 2);
	ft_semfree("/tmp/minishellprintsem");
	free(str);
	exit (code);
}

int	ft_errorreturn(char *reason, char *cmd, int code)
{
	char	*str;

	str = ft_vastrjoin(4, "msh: ", cmd, ": ", reason);
	ft_semwait("/tmp/minishellprintsem");
	ft_putendl_fd(str, 2);
	ft_semfree("/tmp/minishellprintsem");
	free(str);
	return (code);
}

int	ft_moderrorreturn(char *reason, char *cmd, char *cmd2, int code)
{
	char	*str;

	str = ft_vastrjoin(6, "msh: ", cmd, ": ", cmd2, ": ", reason);
	ft_semwait("/tmp/minishellprintsem");
	ft_putendl_fd(str, 2);
	ft_semfree("/tmp/minishellprintsem");
	free(str);
	return (code);
}
