/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/15 15:00:42 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*ft_expandheredoc(char *line, char **delimiter, t_shell shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	i = 0;
	j = 0;
	while ((*delimiter)[i])
	{
		if ((*delimiter)[i] == '\'')
		{
			i++;
			while ((*delimiter)[i] && (*delimiter)[i] != '\'')
			{
				(*delimiter)[j] = (*delimiter)[i];
				i++;
				j++;
			}
			(*delimiter)[j] = '\0'; 
			return (line);
		}
		if ((*delimiter)[i] == '\"')
		{
			i++;
			while ((*delimiter)[i] && (*delimiter)[i] != '\"')
			{
				(*delimiter)[j] = (*delimiter)[i];
				i++;
				j++;
			}
			(*delimiter)[j] = '\0'; 
			return (line);
		}
		i++;
	}
	begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	while (ft_checkoutquotevar(line) >= 0)
	{
		i = 0;
		j = 0;
		while (line[i] && line[i] != '$')
		{
			if (line[i] == '\'')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\'')
				{
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			if (line[i] == '\"')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\"')
				{
					if (line[i] == '$' && line[i + 1] != '\'' && line[i + 1] != '\"' && line[i + 1] != '(')
						break ;
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			if (!line[i] || (line[i] == '$' && line[i + 1] != '\'' && line[i + 1] != '\"' && line[i + 1] != '('))
				break ;
			begin[j] = line[i];
			i++;
			j++;
			if (line[i] == '$' && line[i + 1] == '(')
			{
				while (line[i] != ')')
				{
					begin[j] = line[i];
					j++;
					i++;
				}
				begin[j] = line[i];
				i++;
				j++;
			}
		}
		if (line[i] == '$')
		{
			begin[j] = '\0';
			i++;
		}
		if (line[i] == '?')
		{
			val = ft_itoa(shell.code % 256);
			i++;
		}
		else if (line[i] == '$')
		{
			val = ft_itoa(shell.pid);
			i++;
		}
		else if (line[i] == ' ')
		{
			val = ft_strdup("$");
			i++;
		}
		else if (!line[i])
			val = ft_strdup("$");
		else
		{
			j = 0;
			while ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z' ) || line[i] == '_')
			{
				var[j] = line[i];
				i++;
				j++;
			}
			var[j] = '\0';
			val = ft_getenvval(shell.envp, var);
		}
		j = 0;
		while (line[i])
		{
			rest[j] = line[i];
			i++;
			j++;
		}
		rest[j] = '\0';
		free (line);
		line = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (line);
}

int	ft_heredoc(char **delimiter, char *file, t_shell shell)
{
	int		fdi;
	char	*line;
	int		length;

	fdi = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(*delimiter);
	ft_putstr_fd("minishell heredoc> ", 0);
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, *delimiter, length + 1))
	{
		ft_putstr_fd("minishell heredoc> ", 0);
		line = ft_expandheredoc(line, delimiter, shell);
		ft_putendl_fd(line, fdi);
		// free(line);
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
	char	*hdn;
	int		i;
	int		j;
	char	*tmp;
	char	*start;
	char	*end;
	char	*delimiter;
	char	*frkn;
	char	*cmdn;

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
					frkn = ft_itoa(forknumber);
					cmdn = ft_itoa(icmd);
					hdn = ft_itoa(shell->forks[forknumber].cmds[icmd].heredoc);
					tmp = ft_vastrjoin(8, "/tmp/minishell/heredoc", ".", frkn, ".", cmdn, ".", hdn, ".tmp");
					free(frkn);
					free(cmdn);
					free(hdn);
					shell->forks[forknumber].cmds[icmd].heredoc++;
					ft_heredoc(&delimiter, tmp, *shell);
					free(tmp);
					free(delimiter);
					if (ft_checkoutquote(shell->forks[forknumber].cmds[icmd].pipeline + i, '<', 2) < 0)
					{
						while (shell->forks[forknumber].cmds[icmd].pipeline[i])
						{
							end[j] = shell->forks[forknumber].cmds[icmd].pipeline[i];
							i++;
							j++;
						}
						end[j] = '\0';
						shell->forks[forknumber].cmds[icmd].pipeline = ft_strjoin(start, end);
					}
				}
				else
				{
					start[i] = shell->forks[forknumber].cmds[icmd].pipeline[i];
					i++;
				}
			}
			free(start);
			free(end);
		}
		icmd++;
	}
	return (shell->forks[forknumber]);
}
