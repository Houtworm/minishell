/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:05 by houtworm      #+#    #+#                 */
/*   Updated: 2024/01/13 08:05:04 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_commands cmd, t_shell *msh)
{
	int		i;

	i = 0;
	if (cmd.arg[1] && cmd.arg[1][0] == '-')
		return (ft_errorret2("invalid option", "unset", cmd.arg[1], 2));
	while (msh->envp[i])
	{
		if (!ft_strncmp(msh->envp[i], cmd.arg[1], ft_strlen(cmd.arg[1])))
		{
			free(msh->envp[i]);
			msh->envp[i] = ft_strdup(msh->envp[i + 1]);
			while (msh->envp[i + 1])
			{
				free(msh->envp[i]);
				msh->envp[i] = ft_strdup(msh->envp[i + 1]);
				i++;
			}
			free(msh->envp[i]);
			msh->envp[i] = NULL;
		}
		i++;
	}
	ft_charpptofd(msh->envp, msh);
	return (0);
}
