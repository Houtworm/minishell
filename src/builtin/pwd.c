/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                           |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:00 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/06 17:07:32 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmds cmds, t_shell *shell)
{
	char	*pwd;

	if (cmds.arguments[1])
		if (cmds.arguments[1][0] == '-') // Why is this 5? split_not_quote?
			if (ft_moderrorexit("invalid option", cmds.arguments[1], "pwd", 0)) // still goes here if cd arg is followed by a space
				return (2);
	pwd = ft_getpwd(shell->envp, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
