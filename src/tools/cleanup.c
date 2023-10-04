/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   cleanup.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 01:18:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/04 08:31:48 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freecmds(t_cmds *cmds)
{
	int		i;

	i = 0;
	while (cmds[i].pipeline)
	{
		free(cmds[i].pipeline);
		free(cmds[i].absolute);
		/*ft_frearr(cmds[i].arguments);*/
		/*ft_frearr(cmds[i].outfile);*/
		/*ft_frearr(cmds[i].infile);*/
		/*free(cmds[i].append);*/
		/*ft_frearr(cmds->envp);*/
		i++;
	}
	free(cmds);
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
		free(forks);
	}
}

void	ft_freeexit(t_shell *shell, int code)
{
	ft_freeforks(shell->forks);
	free(shell->alias->val);
	free(shell->alias->var);
	free(shell->alias);
	free(shell->historyfile);
	free(shell->oldline);
	free(shell->line);
	ft_frearr(shell->envp);
	free(shell);
	exit (code);
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
