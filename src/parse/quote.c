/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:08:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/07 03:11:18 by djonker      \___)=(___/                 */
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

int	ft_checkoutquote(char *line, char target, int mode)
{
	int		i;
	char	*quotes;

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
				i++;
				while (!ft_strchr(quotes, line[i]))
					i++;
			}
			i++;
		}
	}
	return (-1);
}

char	check_quote_closed(t_shell *shell)
{
	int		i;
	char	check;

	i = 0;
	check = '\0';
	while (shell->line[i])
	{
		while (shell->line[i] && !check)
		{
			if (shell->line[i] == '\'' || shell->line[i] == '\"' || shell->line[i] == '`' || shell->line[i] == '(')
				check = shell->line[i];
			i++;
		}
		while (shell->line[i] && check)
		{
			if ((shell->line[i] == check) || (shell->line[i] == ')' && check == '('))
				check = '\0';
			i++;
		}
	}
	return (check);
}
