/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:08:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/03 16:55:58 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_closequote(char *line)
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
			if (quote == 1 && ft_strchr(gnl, '\''))
				break ;
			else if (quote == 2 && ft_strchr(gnl, '\"'))
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
			while (tmp[i] == '\"' || tmp[i] == '\'')
			{
				check = tmp[i];
				i++;
			}
			while (tmp[i] && tmp[i] != check)
			{
				cmd[count][k] = tmp[i];
				i++;
				k++;
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