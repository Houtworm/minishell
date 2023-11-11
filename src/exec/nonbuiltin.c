/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nonbuiltin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 20:06:18 by yitoh         #+#    #+#                 */
/*   Updated: 2023/11/11 07:35:01 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_nonbuiltin_child(t_commands *cmd, int c, int f, t_shell *msh)
{
	signal(SIGQUIT, ft_sighandler);
	if (ft_dupmachine(c, f, msh) == 2)
		exit (1);
	if (msh->forks > 1)
	{
		close(msh->pipes[f][1]);
		close(msh->pipes[f][0]);
		close(msh->pipes[f + 1][1]);
		close(msh->pipes[f + 1][0]);
	}
	execve(cmd->abs, cmd->arg, msh->envp);
	ft_errorexit("command not found", (*cmd).abs, 127);
}

void	ft_nonbuiltinfork(t_commands *cmd, int c, int f, t_shell *msh)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_nonbuiltin_child(cmd, c, f, msh);
	if (msh->forks > 1)
	{
		close(msh->pipes[f][1]);
		close(msh->pipes[f][0]);
		close(msh->pipes[f + 1][0]);
	}
	waitpid(pid, &status, 0);
	cmd->code = WEXITSTATUS(status);
}
