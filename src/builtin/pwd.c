/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:00 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:54 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_commands cmd, t_shell *msh)
{
	char	*pwd;

	if (cmd.arg[1])
		if (cmd.arg[1][0] == '-')
			return (ft_errorret2("invalid option", cmd.arg[1], "pwd", 2));
	pwd = ft_getpwd(msh->envp, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
