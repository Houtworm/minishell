/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   complete.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/03 18:38:40 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/03 18:40:04 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
				ft_putstr_fd("> ", 0);
			ret = get_next_line(0, &gnl);
			if (ret == 0)
				break;
			if (gnl[0] == 23)
				ft_errorexit("bla", "bla", 2);
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
