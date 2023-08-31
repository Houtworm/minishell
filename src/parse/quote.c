/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   quote.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <codam@houtworm.net>               //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/30 17:08:32 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/31 17:07:21 by houtworm     \___)=(___/                 */
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
	if (quote)
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
		free(line);
		return (temp);
	}
	return (line);
}
