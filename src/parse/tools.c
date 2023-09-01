/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tools.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 09:00:10 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/01 05:24:26 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
