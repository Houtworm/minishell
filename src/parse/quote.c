/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:08:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/27 09:41:00 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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

char	*ft_closeline(char *line)
{
	int		quote;
	char	*temp;
	int		ret;
	char	*gnl;

	quote = check_quote_closed(line);
	while (quote)
	{
		while (1)
		{
			if (quote)
				ft_putstr("> ");
			ret = get_next_line(0, &gnl);
			if (ret == 0)
				break;
			if (quote == '\'' && ft_strchr(gnl, '\''))
				break ;
			else if (quote == '\"' && ft_strchr(gnl, '\"'))
				break ;
			else if (quote == '`' && ft_strchr(gnl, '`'))
				break ;
			else if (quote == '(' && ft_strchr(gnl, ')'))
				break ;
			else
			{
				temp = ft_vastrjoin(3, line, "\n", gnl);
				free(gnl);
			}
			free(line);
			line = ft_strdup(temp);
		}
		temp = ft_vastrjoin(3, line, "\n", gnl);
		free(gnl);
		/*free(line);*/
		line = ft_strdup(temp);
		free (temp);
		quote = check_quote_closed(line);
	}
	return (line);
}

char	*ft_completeline(char *line, int k)
{	
	char	*temp;
	int		ret;
	char	*gnl;
	int		i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (line[i] == ' ')
		i--;
	if (line[i] != '&' && line[i] != '|')
		return (line);
	while ((line[i] == '&' && line[i - 1] == '&') || line[i] == '|')
	{
		ft_putstr("> ");
		ret = get_next_line(0, &gnl);
		if (ret == 0)
			break;
		// gnl = ft_closeline(gnl);
		while (gnl[k])
			k++;
		while (gnl[k] == ' ')
			k--;
		temp = ft_strjoin(line, gnl);
		free(gnl);
		free(line);
		line = ft_strdup(temp);
		free (temp);
		i += k;
	}
	return (line);
}

char	**ft_remove_quote(char	**cmd, int count)
{
	char	*tmp;
	char	check;
	int		i;
	int		k;

	check = '\0';
	while (cmd[count])
	{
		tmp = cmd[count];
		i = 0;
		k = 0;
		while (tmp[i])
		{
			while ((!check || check == tmp[i]) && (tmp[i] == '\"' || tmp[i] == '\''))
			{
				if (check == tmp[i])
					check = '\0';
				else
					check = tmp[i];
				i++;
			}
			if (check)
			{
				while (tmp[i] && tmp[i] != check)
				{
					cmd[count][k] = tmp[i];
					i++;
					k++;
				}
			}
			else
			{
				while (tmp[i] && tmp[i] != '\"' && tmp[i] != '\'')
				{
					cmd[count][k] = tmp[i];
					i++;
					k++;
				}
			}
		}
		while (cmd[count][k])
		{
			cmd[count][k] = '\0';
			k++;
		}
		count++;
	}
	return (cmd);
}
