/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 01:18:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 10:53:54 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freecommands(t_commands *cmd)
{
	int		i;

	i = 0;
	while (cmd[i].pipeline)
	{
		free(cmd[i].pipeline);
		free(cmd[i].absolute);
		if (cmd[i].arg)
			ft_frearr(cmd[i].arg);
		if (cmd[i].outfile)
		ft_frearr(cmd[i].outfile);
		if (cmd[i].infile)
		ft_frearr(cmd[i].infile);
		if (cmd[i].append)
		free(cmd[i].append);
		i++;
	}
	free(cmd);
}

void	ft_freeforks(t_forks *frk)
{
	int		i;

	i = 0;
	if (frk)
	{
		while (frk[i].cmd)
		{
			ft_freecommands(frk[i].cmd);
			free(frk[i].pipeline);
			i++;
		}
		free(frk[i].cmd);
	}
	free(frk);
}

void	ft_freeexit(t_shell *shell, int code)
{
	int	i;

	ft_rmdir("/tmp/minishell", shell->envp);
	ft_freeforks(shell->frk);
	free(shell->alias->val);
	free(shell->alias->var);
	free(shell->alias);
	free(shell->historyfile);
	free(shell->oldline);
	free(shell->line);
	ft_frearr(shell->envp);
	i = 0;
	while (i < 13)
	{
		free(shell->builtins[i].compare);
		i++;
	}
	free(shell->builtins);
	free(shell->os);
	/*free(shell);*/
	exit (code);
}

void	ft_freenewprompt(t_shell *shell)
{
	int	i;

	ft_freeforks(shell->frk);
	i = 0;
	if (shell->forkamount > 1)
	{
		while (shell->forkamount >= i)
		{
			free(shell->pipes[i]);
			i++;
		}
		free(shell->pipes[i]);
		free(shell->pipes);
	}
	shell->stop = 0;
	unlink("/tmp/minishell/lastcode.tmp");
}

void	ft_freeglobs(t_globs *globs)
{
	free(globs->pipeline);
	free(globs->gstart);
	free(globs->gend);
	free(globs->start);
	free(globs->end);
	free(globs->glob);
	free(globs->anyof);
	free(globs->pardir);
	free(globs->backup);
	ft_frearr(globs->subdir);
	ft_frearr(globs->tempsubdir);
	ft_frearr(globs->matches);
	free(globs);
}
