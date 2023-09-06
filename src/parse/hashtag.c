/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   hashtag.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 21:08:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/04 21:55:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsehashtag(char *line)
{
	/*char	*temp;*/
	int		i;

	if (ft_checkoutquote(line, '#', 2) >= 0)
	{
		i = 0;
		if (line[0] == '#')
			line[0] = '\0';
		while (line[i] && (line[i] != ' ' || line[i - 1] != '#'))
		{
			if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\'')
					i++;
				i++;
			}
			if (line[i] == '\"')
			{
				i++;
				while (line[i] != '\"')
					i++;
				i++;
			}
		// printf ("line[%d] = %c\n", i, line[i]);
			i++;
		}
		/*temp = ft_substr(line, 0, i);*/
		/*free(line);*/
		/*line = ft_strdup(temp);*/
		/*free(temp);*/
		line = ft_substr(line, 0, i - 1); // memory leak, but we need to fix a bug in the parser for this.
	}
		// printf ("line = %s\n", line);
	return (line);
}
