/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/01 00:57:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/22 03:09:42 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exec(t_commands cmd, t_shell *msh)
{
	int		i;
	int		status;
	char	**paths;
	char	**args;

	i = 0;
	paths = ft_getpaths(msh->envp, 1);
	args = ft_calloc(1000, 8);
	while (cmd.arg[i + 1])
	{
		args[i] = ft_strdup(cmd.arg[i + 1]);
		i++;
	}
	free(cmd.abs);
	cmd.abs = ft_abspathcmd(paths, args[0]);
	ft_frearr(paths);
	status = ft_checkcommand(args, msh->envp);
	if (status)
		status = 127;
	else
		execve(cmd.abs, args, msh->envp);
	ft_frearr(args);
	free(cmd.abs);
	return (status);
}
