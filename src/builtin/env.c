/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                           |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:16 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 03:58:26 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_commands cmd, t_shell *msh)
{
	int		i;
	char	*str;

	i = 0;
	if (cmd.arg[1])
	{
		if (cmd.arg[1][0] == '-')
			return (ft_errorret2(cmd.arg[1], "env", "invalid option", 125));
		else
		{
			str = ft_strdup("No such file or directory");
			ft_errorret2(str, "env", cmd.arg[1], 127);
			free(str);
			return (127);
		}
	}
	if (cmd.arg[0][3] == ' ')
		return (ft_errorret2("command not found", "env", cmd.arg[1], 127));
	while (msh->envp[i])
	{
		ft_putendl(msh->envp[i]);
		i++;
	}
	return (0);
}
