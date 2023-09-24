/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/08/30 18:20:05 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_countpipe(char *line, int count, int i)
{
	while (line[i])
	{
		while (line[i] && line[i] != '|')
			i++;
		while (line[i] && (line[i] == '\'' || line[i] == '\"'))
		{
			i = ft_skipquote(line, i) + 1;
			while (line[i] == ' ')
				i++;
			while (line[i] != '|')
				i++;
		}
		if (line[i] == '|')
		{
			i++;
			if (line[i] != '|')
				count++;
			else
				i++;
		}
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (count);
}

char	**split_pipe(char *line, int start, int pipecount)
{

	int		i;
	char	**cmd;

	i = 0;
	pipecount = ft_countpipe(line, 0, 0) + 1;
	cmd = ft_calloc(pipecount, sizeof(char *));
	if (!cmd)
		ft_errorexit("Error allocating memory", "malloc", 1);
	if (pipecount == 1)
	{
		cmd[i] = ft_strdup(line);
		return (cmd);
	}
	while (i < pipecount)
	{
		while (line[start] == '|')
			start++;
		cmd[i] = ft_substr(line, start, count_wd(line + start, '|'));
		if (!cmd[i])
			return (ft_frenarr(cmd, i));
		start += count_wd(line + start, '|');
		i++;
	}
	return (cmd);

}


t_shell	ft_parsepipe(char *line, t_shell shell)
{
	char	**tmp;

	shell.forkamount = 0;
	shell.line = ft_strdup(line);
	shell.forks = ft_calloc(1000 * sizeof(t_forks), 1);
	tmp = split_not_quote(line, '|');
	// tmp = split_pipe(line, 0, 0);
	while (tmp[shell.forkamount])
	{
		shell.forks[shell.forkamount].pipeline = ft_strdup(tmp[shell.forkamount]);
		shell.forkamount++;
	}
	ft_frearr(tmp);
	return (shell);
}
