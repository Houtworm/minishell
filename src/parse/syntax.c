/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   syntax.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 13:48:26 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/25 19:46:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_syntaxerror(t_shell *shell, char s1, char *line, int i)
{
	int		j;
	char	*help;

	ft_putstr_fd("Syntax Error: ", 2);
	ft_printinsult(shell);
	ft_putstr_fd("\nyou can't follow up this ", 2);
	ft_putchar_fd(s1, 2);
	ft_putendl_fd(" like that..", 2);
	help = ft_calloc(ft_strlen(line), 8);
	j = 0;
	while (j < i)
	{
		help[j] = ' ';
		j++;
	}
	help[j] = '^';
	help[j + 1] = '\0';
	ft_putendl_fd(line, 2);
	ft_putendl_fd(help, 2);
	shell->code = 2;
	free(help);
	return (1);
}

int		ft_checksymbol(char *line, int i)
{
	int		j;
	j = 1;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";>&|", line[i + j]))
		return (0);
	return (j);
}

int		ft_checksymbols(char *line, int i, char symbol)
{
	int		j;
	j = 1;
	if (line[i + j] == symbol)
		j++;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";>&|", line[i + j]))
		return (0);
	return (j);
}

int		ft_checksyntax(t_shell *shell, char *line)
{
	int	i;
	int	t;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("<>&|;", line[i]))
		{
			if (line[i] == '<')
			{
				t = ft_checksymbols(line, i, '<');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '<', line, i));
			}
			if (line[i] == '>')
			{
				t = ft_checksymbols(line, i, '>');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '>', line, i));
			}
			if (line[i] == '&')
			{
				t = ft_checksymbols(line, i, '&');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '&', line, i));
			}
			if (line[i] == '|')
			{
				t = ft_checksymbols(line, i, '|');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '|', line, i));
			}
			if (line[i] == ';')
			{
				t = ft_checksymbol(line, i);
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, ';', line, i));
			}
		}
		i++;
	}
	return (0);
}
