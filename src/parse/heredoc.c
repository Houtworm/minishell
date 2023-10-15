/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/15 08:26:58 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_heredoc(char *delimiter, char *file)
{
	int		fdi;
	char	*line;
	int		length;

	fdi = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(delimiter);
	ft_putstr_fd("minishell heredoc> ", 0);
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, delimiter, length + 1))
	{
		ft_putstr_fd("minishell heredoc> ", 0);
		ft_putendl_fd(line, fdi);
		free(line);
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
	}
	free(line);
	close(fdi);
	return (fdi);
}

t_forks ft_parseheredoc(t_shell *shell, int forknumber)
{
	int		icmd;
	int		hdid;
	int		i;
	int		j;
	char	*tmp;
	char	*start;
	char	*end;
	char	*delimiter;
	char	*frkn;
	char	*cmdn;

	hdid = 1;
	icmd = 0;
	i = 0;
	while (icmd < shell->forks[forknumber].cmdamount)
	{
		shell->forks[forknumber].cmds[icmd].heredoc = 0;
		if (ft_checkoutquote(shell->forks[forknumber].cmds[icmd].pipeline, '<', 2) >= 0)
		{
			start = ft_calloc(ft_strlen(shell->forks[forknumber].cmds[icmd].pipeline), 8);
			end = ft_calloc(ft_strlen(shell->forks[forknumber].cmds[icmd].pipeline), 8);
			while (shell->forks[forknumber].cmds[icmd].pipeline[i])
			{
				if (shell->forks[forknumber].cmds[icmd].pipeline[i] == '\'')
				{
					start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
					i++;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i] != '\'' && shell->forks[forknumber].cmds[icmd].pipeline[i])
					{
						start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
						i++;
					}
					i++;
				}
				else if (shell->forks[forknumber].cmds[icmd].pipeline[i] == '\"')
				{
					start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
					i++;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i] != '\"' && shell->forks[forknumber].cmds[icmd].pipeline[i])
					{
						start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
						i++;
					}
					i++;
				}
				else if (shell->forks[forknumber].cmds[icmd].pipeline[i] == '<' && shell->forks[forknumber].cmds[icmd].pipeline[i + 1] == '<')
				{
					delimiter = ft_calloc(ft_strlen(shell->forks[forknumber].cmds[icmd].pipeline), 8);
					start[i] = '\0';
					i = i + 2;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i] == ' ')
						i++;
					j = 0;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i] && shell->forks[forknumber].cmds[icmd].pipeline[i] != ' ')
					{
						delimiter[j] = shell->forks[forknumber].cmds[icmd].pipeline[i];
						i++;
						j++;
					}
					delimiter[j] = '\0';
					j = 0;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i] == ' ')
						i++;
					while (shell->forks[forknumber].cmds[icmd].pipeline[i])
					{
						end[j] = shell->forks[forknumber].cmds[icmd].pipeline[i];
						i++;
						j++;
					}
					end[j] = '\0';
					frkn = ft_itoa(forknumber);
					cmdn = ft_itoa(icmd);
					tmp = ft_vastrjoin(6, "/tmp/minishell/heredoc", ".", frkn, ".", cmdn, ".tmp");
					free(frkn);
					free(cmdn);
					shell->forks[forknumber].cmds[icmd].heredoc = 1;
					ft_heredoc(delimiter, tmp);
					shell->forks[forknumber].cmds[icmd].pipeline = ft_strjoin(start, end);
					free(tmp);
					free(delimiter);
				}
				else
				{
					start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
					i++;
				}
			}
			free(start);
			free(end);
			hdid++;
		}
		icmd++;
	}
	return (shell->forks[forknumber]);
}
