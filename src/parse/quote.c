/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:08:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/03 18:41:40 by houtworm     \___)=(___/                 */
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

char	check_quote_closed(char *s)
{
	int		i;
	char	check;

	i = 0;
	check = '\0';
	while (s[i])
	{
		while (s[i] && !check)
		{
			if (s[i] == '\'' || s[i] == '\"' || s[i] == '`' || s[i] == '(')
				check = s[i];
			i++;
		}
		while (s[i] && check)
		{
			if ((s[i] == check) || (s[i] == ')' && check == '('))
				check = '\0';
			i++;
		}
	}
	return (check);
}

/*char	**ft_remove_quote(char	**cmd, int count)*/
/*{*/
	/*char	*tmp;*/
	/*char	check;*/
	/*int		i;*/
	/*int		k;*/

	/*check = '\0';*/
	/*while (cmd[count])*/
	/*{*/
		/*tmp = cmd[count];*/
		/*i = 0;*/
		/*k = 0;*/
		/*while (tmp[i])*/
		/*{*/
			/*while ((!check || check == tmp[i]) && (tmp[i] == '\"' || tmp[i] == '\''))*/
			/*{*/
				/*if (check == tmp[i])*/
					/*check = '\0';*/
				/*else*/
					/*check = tmp[i];*/
				/*i++;*/
			/*}*/
			/*if (check)*/
			/*{*/
				/*while (tmp[i] && tmp[i] != check)*/
				/*{*/
					/*cmd[count][k] = tmp[i];*/
					/*i++;*/
					/*k++;*/
				/*}*/
			/*}*/
			/*else*/
			/*{*/
				/*while (tmp[i] && tmp[i] != '\"' && tmp[i] != '\'')*/
				/*{*/
					/*cmd[count][k] = tmp[i];*/
					/*i++;*/
					/*k++;*/
				/*}*/
			/*}*/
		/*}*/
		/*while (cmd[count][k])*/
		/*{*/
			/*cmd[count][k] = '\0';*/
			/*k++;*/
		/*}*/
		/*count++;*/
	/*}*/
	/*return (cmd);*/
/*}*/
