/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 01:18:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/24 18:43:09 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freecommands(t_commands *cmd)
{
	int		i;

	i = 0;
	while (cmd[i].line)
	{
		free(cmd[i].line);
		free(cmd[i].abs);
		if (cmd[i].arg)
			ft_frearr(cmd[i].arg);
		if (cmd[i].ofi)
			ft_frearr(cmd[i].ofi);
		if (cmd[i].app)
			free(cmd[i].app);
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
			free(frk[i].line);
			i++;
		}
		free(frk[i].cmd);
	}
	free(frk);
}

void	ft_freeexit(t_shell *msh, int code)
{
	/*int		i;*/

	ft_rmdir(msh->tmpdir, msh->envp);
	/*ft_freeforks(msh->frk);*/
	/*free(msh->alias->val);*/
	/*free(msh->alias->var);*/
	/*free(msh->alias);*/
	/*free(msh->historyfile);*/
	/*free(msh->oldline);*/
	/*free(msh->line);*/
	/*ft_frearr(msh->envp);*/
	/*i = 0;*/
	/*while (i < 13)*/
	/*{*/
		/*free(msh->bltn[i].cmnd);*/
		/*i++;*/
	/*}*/
	/*free(msh->bltn);*/
	/*free(msh->os);*/
	exit (code);
}

void	ft_freenewprompt(t_shell *msh)
{
	int		i;
	char	*file;

	ft_freeforks(msh->frk);
	i = 0;
	if (msh->forks > 1)
	{
		while (msh->forks >= i)
		{
			free(msh->pipes[i]);
			i++;
		}
		free(msh->pipes[i]);
		free(msh->pipes);
	}
	file = ft_strjoin(msh->tmpdir, "lastcode.tmp");
	unlink(file);
	free(file);
}

void	ft_freeglobs(t_globs *globs)
{
	free(globs->line);
	free(globs->gsta);
	free(globs->gend);
	free(globs->start);
	free(globs->end);
	free(globs->glob);
	free(globs->pdir);
	free(globs->backup);
	ft_frearr(globs->sdir);
	ft_frearr(globs->tmpsdir);
	ft_frearr(globs->matches);
	free(globs);
}
