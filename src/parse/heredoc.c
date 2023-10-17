/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/17 22:22:17 by houtworm     \___)=(___/                 */
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

void	ft_readstdinheredoc(char *delimiter, int parse, int fdi, t_shell msh)
{
	char	*line;
	int		length;

	length = ft_strlen(delimiter);
	ft_putstr_fd("minishell heredoc> ", 0);
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "ft_heredoc", 1);
	while (ft_strncmp(line, delimiter, length + 1))
	{
		ft_putstr_fd("minishell heredoc> ", 0);
		if (parse)
			line = ft_parsevariable(line, msh, 0);
		ft_putendl_fd(line, fdi);
		free(line);
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "ft_heredoc", 1);
	}
	free(line);
}

int	ft_heredoc(char *delimiter, char *file, t_shell msh, int heredoc)
{
	int		fdi;
	size_t	length;
	int		parse;

	heredoc = heredoc;
	/*if (heredoc) // comment this line for bash behavior*/
		/*fdi = open(file, O_RDWR | O_CREAT | O_APPEND, 0666); // comment this line for bash behavior*/
	/*else // comment this line for bash behavior*/
		fdi = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(delimiter);
	parse = 1;
	delimiter = ft_checkdelimiter(delimiter);
	if (ft_strlen(delimiter) < length)
		parse = 0;
	ft_readstdinheredoc(delimiter, parse, fdi, msh);
	close(fdi);
	return (fdi);
}
