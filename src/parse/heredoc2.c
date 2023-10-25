/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 03:38:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/25 05:27:18 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_checkdelimiter(char *delimiter)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '\"')
		{
			quote = delimiter[i];
			i++;
			while (delimiter[i] && delimiter[i] != quote)
			{
				delimiter[j] = delimiter[i];
				i++;
				j++;
			}
			delimiter[j] = '\0';
			return (delimiter);
		}
		i++;
	}
	return (delimiter);
}

int	ft_heredocfork(char *dl, int parse, int fdi, t_shell msh)
{
	char	*line;
	int		length;

	length = ft_strlen(dl);
	signal(SIGINT, ft_sighandlerheredoc);
	line = readline("minishell heredoc>");
	if (!line)
		exit (ft_errorret2("delimited by EOF char", "expected", dl, 0));
	while (ft_strncmp(line, dl, length + 1))
	{
		if (parse)
			line = ft_parsevar(line, msh, 0);
		ft_putendl_fd(line, fdi);
		free(line);
		line = readline("minishell heredoc>");
		if (!line)
			exit (ft_errorret2("delimited by EOF char", "expected", dl, 0));
	}
	free(line);
	exit (0);
}

int	ft_readstdinheredoc(char *delimiter, int parse, int fdi, t_shell msh)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(ft_heredocfork(delimiter, parse, fdi, msh));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_heredoc(char *delimiter, char *file, t_shell msh, int heredoc)
{
	int		fdi;
	size_t	length;
	int		parse;

	if (heredoc)
		fdi = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fdi = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(delimiter);
	parse = 1;
	delimiter = ft_checkdelimiter(delimiter);
	if (ft_strlen(delimiter) < length)
		parse = 0;
	if (ft_readstdinheredoc(delimiter, parse, fdi, msh))
	{
		close(fdi);
		ft_freeforks(msh.frk);
		return (1);
	}
	close(fdi);
	return (0);
}
