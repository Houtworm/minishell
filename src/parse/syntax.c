/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   syntax.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 13:48:26 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/27 10:07:55 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_syntaxerror(t_shell *shell, char s1, char *line, int i)
{
	int		j;
	char	*help;

	ft_putstr_fd("Syntax Error: ", 2);
	ft_printinsult(shell);
	ft_putstr_fd("you can't follow up this ", 2);
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
	return (2);
}

int		ft_checksmallerthan(t_shell *shell, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '<' || line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";<&|", line[i + j]))
		return (ft_syntaxerror(shell, '<', line, i));
	return (0);
}

int		ft_checkgreaterthan(t_shell *shell, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";<>&|", line[i + j]))
		return (ft_syntaxerror(shell, '>', line, i));
	return (0);
}

int		ft_checkampersand(t_shell *shell, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '&')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(shell, '&', line, i));
	return (0);
}

int		ft_checkpipe(t_shell *shell, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '|')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(shell, '|', line, i));
	return (0);
}

int		ft_checksemicolon(t_shell *shell, char *line, int i)
{
	int		j;

	j = 1;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(shell, ';', line, i));
	return (0);
}

int		ft_checksyntax(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			i++;
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			i++;
		}
		else if (line[i] && ft_strchr("<>&|;", line[i]))
		{
			if (line[i] == '<')
				if (ft_checksmallerthan(shell, line, i))
					return (1);
			if (line[i] == '>')
				if (ft_checkgreaterthan(shell, line, i))
					return (1);
			if (line[i] == '&')
				if (ft_checkampersand(shell, line, i))
					return (1);
			if (line[i] == '|')
				if (ft_checkpipe(shell, line, i))
					return (1);
			if (line[i] == ';')
				if (ft_checksemicolon(shell, line, i))
					return (1);
		}
		if (line[i] == '#' && line[i - 1] == ' ')
			return (0);
		else if (line[i])
			i++;
	}
	return (0);
}

int	ft_startsyntax(t_shell *shell, char *line)
{
	int	i;
	int		j;
	char	*help;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == '&' || line[i] == ';')
	{

		ft_putstr_fd("Syntax Error: ", 2);
		ft_printinsult(shell);
		ft_putstr_fd("you can't start with a ", 2);
		ft_putchar_fd(line[i], 2);
		ft_putendl_fd(" symbol", 2);
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
	return (0);
}
