/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 01:18:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/07 15:03:58 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freecmds(t_cmds *cmds)
{
	int		i;

	i = 0;
	while (cmds[i].pipeline)
	{
		// free(cmds[i].pipeline);
		free(cmds[i].absolute);
		if (cmds[i].arguments)
			ft_frearr(cmds[i].arguments); // crashes with tester, needs an if
		if (cmds[i].outfile)
		ft_frearr(cmds[i].outfile);
		if (cmds[i].infile)
		ft_frearr(cmds[i].infile);
		if (cmds[i].append)
		free(cmds[i].append);
		i++;
	}
	// free(cmds);
}

void	ft_freeforks(t_forks *forks)
{
	int		i;

	i = 0;
	if (forks)
	{
		while (forks[i].cmds)
		{
			ft_freecmds(forks[i].cmds);
			free(forks[i].pipeline);
			i++;
		}
		free(forks[i].cmds);
	}
	free(forks);
}

void	ft_freeexit(t_shell *shell, int code)
{
	// int		i;
	
	// ft_freeforks(shell->forks);
	// free(shell->alias->val);
	// free(shell->alias->var);
	// free(shell->alias);
	// free(shell->historyfile);
	// free(shell->oldline);
	// free(shell->line);
	// i = 0;
	// if (shell->forkamount > 1)
	// {
	// 	while (shell->forkamount >= i)
	// 	{
	// 		free(shell->pipes[i]);
	// 		i++;
	// 	}
	// 	free(shell->pipes[i]);
	// 	free(shell->pipes);
	// }
	// ft_frearr(shell->envp);
	// i = 0;
	// while (i < 13)
	// {
	// 	free(shell->builtins[i].compare);
	// 	i++;
	// }
	// free(shell->builtins);
	// free(shell);
	shell = shell;
	exit (code);
}

void	ft_freenewprompt(t_shell *shell)
{
	int	i;

	// ft_freeforks(shell->forks);
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
	/*free(shell->line);*/
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
	ft_frearr(globs->subdir);
	ft_frearr(globs->tempsubdir);
	ft_frearr(globs->matches);
	free(globs);
}
