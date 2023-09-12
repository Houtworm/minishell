/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/12 21:03:10 by yitoh         ########   odam.nl         */
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
	ft_putstr("minishell heredoc> ");
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, delimiter, length + 1))
	{
		ft_putstr("minishell heredoc> ");
		ft_putendl_fd(line, fdi);
		free(line);
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
	}
	free(line);
	close(fdi);
	fdi = open(file, O_RDONLY); // 1 file for multiple heredocs will fail ofc
	return (fdi);
}

char	*ft_delimeter(char *line)
{
	char		**delimeter;
	char		**tmp;
	int			i;

	i = 0;
	delimeter = NULL;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '<' && line[i - 1] == '<')
		{
			i++;
			tmp = split_not_quote(line + i, ' ');
			delimeter = split_not_quote(tmp[0], '>');
			break ;
		}
		i++;
	}
	return (delimeter[0]);
}


void	ft_parseheredoc(t_forks forks, int cmdnum)
{
	int		icmd;
	int		hdid;
	int		i;
	char	*tmp;

	hdid = 1;
	icmd = 0;
	i = 0;
	while (icmd < cmdnum)
	{
		if (ft_strchr(forks.cmds[icmd].pipeline, '<'))
		{
			while (forks.cmds[icmd].pipeline[i] && forks.cmds[icmd].pipeline[i] != '<')
				i++;
			if (!forks.cmds[icmd].pipeline[i])
				return ;
			i += 2;
			if (forks.cmds[icmd].pipeline[i - 2] != '<' && forks.cmds[icmd].pipeline[i - 1] != '<')
				return ;
			tmp = ft_strjoin("/tmp/minishellheredocfile", ft_itoa(hdid));
			forks.cmds[icmd].hdfd = ft_heredoc(ft_delimeter(forks.cmds[icmd].pipeline), ft_strjoin(tmp, ".tmp"));
			hdid++;
		}
		icmd++;
	}
}
