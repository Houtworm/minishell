/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                           |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:00 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/07 02:49:28 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmds cmds, t_shell *shell)
{
	char	*pwd;

	if (cmds.arguments[1])
		if (cmds.arguments[1][0] == '-')
			return (ft_moderrorreturn("invalid option", cmds.arguments[1], "pwd", 2));
	pwd = ft_getpwd(shell->envp, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
