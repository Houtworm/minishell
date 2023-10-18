/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:48:26 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:13 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_syntaxerror(t_shell *msh, char s1, char *line, int i)
{
	int		j;
	char	*help;

	ft_putstr_fd("Syntax Error: ", 2);
	ft_printinsult(msh);
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
	msh->code = 2;
	free(help);
	return (2);
}

int		ft_checksmallerthan(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '<' || line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";<&|", line[i + j]))
		return (ft_syntaxerror(msh, '<', line, i));
	return (0);
}

int		ft_checkgreaterthan(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";<>&|", line[i + j]))
		return (ft_syntaxerror(msh, '>', line, i));
	return (0);
}

int		ft_checkampersand(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '&')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, '&', line, i));
	return (0);
}

int		ft_checkpipe(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '|')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (!line[i + j] || ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, '|', line, i));
	return (0);
}

int		ft_checksemicolon(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, ';', line, i));
	return (0);
}

int		ft_checksyntax(t_shell *msh)
{
	int	i;

	i = 0;
	while (msh->line[i])
	{
		if (msh->line[i] == '\'')
		{
			i++;
			while (msh->line[i] && msh->line[i] != '\'')
				i++;
			if (msh->line[i])
				i++;
		}
		else if (msh->line[i] == '\"')
		{
			i++;
			while (msh->line[i] && msh->line[i] != '\"')
				i++;
			if (msh->line[i])
				i++;
		}
		else if (msh->line[i] && ft_strchr("<>&|;", msh->line[i]))
		{
			if (msh->line[i] == '<')
				if (ft_checksmallerthan(msh, msh->line, i))
					return (1);
			if (msh->line[i] == '>')
				if (ft_checkgreaterthan(msh, msh->line, i))
					return (1);
			if (msh->line[i] == '&')
				if (ft_checkampersand(msh, msh->line, i))
					return (1);
			if (msh->line[i] == '|')
				if (ft_checkpipe(msh, msh->line, i))
					return (1);
			if (msh->line[i] == ';')
				if (ft_checksemicolon(msh, msh->line, i))
					return (1);
		}
		if (msh->line[i] && i > 0 && msh->line[i] == '#' && msh->line[i - 1] == ' ')
			return (0);
		else if (msh->line[i])
			i++;
	}
	return (0);
}

int	ft_startsyntax(t_shell *msh)
{
	int	i;
	int		j;
	char	*help;

	i = 0;
	while (msh->line[i] == ' ')
		i++;
	if (msh->line[i] == '|' || msh->line[i] == '&' || msh->line[i] == ';')
	{

		ft_putstr_fd("Syntax Error: ", 2);
		ft_printinsult(msh);
		ft_putstr_fd("you can't start with a ", 2);
		ft_putchar_fd(msh->line[i], 2);
		ft_putendl_fd(" symbol", 2);
		help = ft_calloc(ft_strlen(msh->line), 8);
		j = 0;
		while (j < i)
		{
			help[j] = ' ';
			j++;
		}
		help[j] = '^';
		help[j + 1] = '\0';
		ft_putendl_fd(msh->line, 2);
		ft_putendl_fd(help, 2);
		msh->code = 2;
		free(help);
		return (1);
	}
	return (0);
}
