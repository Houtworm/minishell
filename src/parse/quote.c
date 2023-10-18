/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:08:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 21:38:33 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipquote(char *s, int i)
{
	int	k;

	k = 0;
	if (s[i] == '\"' || (s[i] == '\''))
	{
		k++;
		while (s[i + k] != s[i] && s[i + k])
			k++;
		if (!s[i + k])
			return (-1);
	}
	return (i + k);
}

int	ft_checkoutquotevar(char *line)
{
	int		i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '$' && line[i + 1] && ((line[i + 1] >= 'A' && line[i + 1] <= 'Z') || (line[i + 1] >= 'a' && line[i + 1] <= 'z' ) || ft_strchr("_?$\"\'", line[i + 1])))
				return (i);
			if (line[i] == '\"')
			{
				i++;
				while (line[i] != '\"')
				{
					if (line[i] == '$' && line[i + 1] && ((line[i + 1] >= 'A' && line[i + 1] <= 'Z') || (line[i + 1] >= 'a' && line[i + 1] <= 'z' ) || ft_strchr("_?$", line[i + 1])))
						return (i);
					i++;
				}
			}
			if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\'')
					i++;
			}
			i++;
		}
	}
	return (-1);
}

int	ft_checkoutquote(char *line, char target, int mode)
{
	int		i;
	char	*quotes;
	char	quote;

	i = 0;
	quotes = "\'";
	if (mode == 2)
		quotes = "\'\"";
	if (line)
	{
		while (line[i])
		{
			if (line[i] == target)
				return (i);
			if (ft_strchr(quotes, line[i]))
			{
				quote = line[i];
				i++;
				while (quote != line[i])
					i++;
			}
			i++;
		}
	}
	return (-1);
}

int	ft_checkoutquote2(char *line, char target, char target2, int mode)
{
	int		i;
	char	*quotes;
	char	quote;

	i = 0;
	quotes = "\'";
	if (mode == 2)
		quotes = "\'\"";
	if (line)
	{
		while (line[i])
		{
			if (line[i] == target && line[i + 1] == target2)
				return (i);
			if (ft_strchr(quotes, line[i]))
			{
				quote = line[i];
				i++;
				while (quote != line[i])
					i++;
			}
			i++;
		}
	}
	return (-1);
}

char	check_quote_closed(t_shell *msh)
{
	int		i;
	char	check;

	i = 0;
	check = '\0';
	while (msh->line[i])
	{
		while (msh->line[i] && !check)
		{
			if (msh->line[i] == '\'' || msh->line[i] == '\"'
				|| msh->line[i] == '`' || msh->line[i] == '(')
				check = msh->line[i];
			i++;
		}
		while (msh->line[i] && check)
		{
			if ((msh->line[i] == check) || (msh->line[i] == ')'
					&& check == '('))
				check = '\0';
			i++;
		}
	}
	return (check);
}
