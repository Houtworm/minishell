/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 23:51:19 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*ft_expandheredoc(char *line, char **delimiter, t_shell msh)
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
			val = ft_itoa(msh.code % 256);
			i++;
		}
		else if (line[i] == '$')
		{
			val = ft_itoa(msh.pid);
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
			val = ft_getenvval(msh.envp, var);
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

int	ft_heredoc(char **delimiter, char *file, t_shell msh, int heredoc)
{
	int		fdi;
	char	*line;
	int		length;

	if (heredoc)
		fdi = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fdi = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(*delimiter);
	ft_putstr_fd("minishell heredoc> ", 0);
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, *delimiter, length + 1))
	{
		ft_putstr_fd("minishell heredoc> ", 0);
		line = ft_expandheredoc(line, delimiter, msh);
		ft_putendl_fd(line, fdi);
		 /*free(line);*/
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
	}
	free(line);
	close(fdi);
	return (fdi);
}

t_forks ft_parseheredoc(t_shell *msh, int forknumber)
{
	int		icmd;
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
	while (icmd < msh->frk[forknumber].cmdamount)
	{
		msh->frk[forknumber].cmd[icmd].heredoc = 0;
		if (ft_checkoutquote(msh->frk[forknumber].cmd[icmd].pipeline, '<', 2) >= 0)
		{
			start = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].pipeline), 8);
			end = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].pipeline), 8);
			while (msh->frk[forknumber].cmd[icmd].pipeline[i])
			{
				if (msh->frk[forknumber].cmd[icmd].pipeline[i] == '\'')
				{
					start[i] = msh->frk[forknumber].cmd[icmd].pipeline[i];
					i++;
					while (msh->frk[forknumber].cmd[icmd].pipeline[i] != '\'' && msh->frk[forknumber].cmd[icmd].pipeline[i])
					{
						start[i] = msh->frk[forknumber].cmd[icmd].pipeline[i];
						i++;
					}
					i++;
				}
				else if (msh->frk[forknumber].cmd[icmd].pipeline[i] == '\"')
				{
					start[i] = msh->frk[forknumber].cmd[icmd].pipeline[i];
					i++;
					while (msh->frk[forknumber].cmd[icmd].pipeline[i] != '\"' && msh->frk[forknumber].cmd[icmd].pipeline[i])
					{
						start[i] = msh->frk[forknumber].cmd[icmd].pipeline[i];
						i++;
					}
					i++;
				}
				else if (msh->frk[forknumber].cmd[icmd].pipeline[i] == '<' && msh->frk[forknumber].cmd[icmd].pipeline[i + 1] == '<')
				{
					delimiter = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].pipeline), 8);
					start[i] = '\0';
					i = i + 2;
					while (msh->frk[forknumber].cmd[icmd].pipeline[i] == ' ')
						i++;
					j = 0;
					while (msh->frk[forknumber].cmd[icmd].pipeline[i] && msh->frk[forknumber].cmd[icmd].pipeline[i] != ' ')
					{
						delimiter[j] = msh->frk[forknumber].cmd[icmd].pipeline[i];
						i++;
						j++;
					}
					delimiter[j] = '\0';
					j = 0;
					while (msh->frk[forknumber].cmd[icmd].pipeline[i] == ' ')
						i++;
					frkn = ft_itoa(forknumber);
					cmdn = ft_itoa(icmd);
					tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
					free(frkn);
					free(cmdn);
					ft_heredoc(&delimiter, tmp, *msh, msh->frk[forknumber].cmd[icmd].heredoc);
					msh->frk[forknumber].cmd[icmd].heredoc++;
					free(tmp);
					free(delimiter);
					if (ft_checkoutquote(msh->frk[forknumber].cmd[icmd].pipeline + i, '<', 2) < 0)
					{
						while (msh->frk[forknumber].cmd[icmd].pipeline[i])
						{
							end[j] = msh->frk[forknumber].cmd[icmd].pipeline[i];
							i++;
							j++;
						}
						end[j] = '\0';
						msh->frk[forknumber].cmd[icmd].pipeline = ft_strjoin(start, end);
					}
				}
				else
				{
					start[i] = msh->frk[forknumber].cmd[icmd].pipeline[i];
					i++;
				}
			}
			free(start);
			free(end);
		}
		icmd++;
	}
	return (msh->frk[forknumber]);
}
