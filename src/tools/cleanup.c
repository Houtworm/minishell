/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   cleanup.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 01:18:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/04 04:56:38 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freecmds(t_cmds *cmds)
{
	free(cmds);
}

void	ft_freeforks(t_forks *forks)
{
	int		i;

	i = 0;
	while (forks[i].cmds)
	{
		ft_freecmds(forks[i].cmds);
		i++;
	}
	free(forks);
}

void	ft_freeexit(t_shell *shell, int code)
{
	/*ft_freeforks(shell->forks);*/
	free(shell->alias->val);
	free(shell->alias->var);
	free(shell->alias);
	free(shell->historyfile);
	free(shell->oldline);
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
