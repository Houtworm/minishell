/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tools.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 09:00:10 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/27 10:34:35 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_findcharoutquote(char *line, char target, char quote) // subfunction of checkoutquote
{
	int		i;

	i = 0;

	if (line)
	{
		while (line[i])
		{
			if (line[i] == target)
				return (1);
			if (line[i] == quote)
			{
				i++;
				while (line[i] != quote)
					i++;
			}
			i++;
		}
	}
	return (0);
}

int	ft_checkoutquote(char *line, char target, int mode) // used to check if we actually need to run the parse functions to save time.
{
	if (mode > 0)
		if (ft_findcharoutquote(line, target, '\''))
			return (1);
	if (mode == 2)
		if (ft_findcharoutquote(line, target, '\"'))
			return (1);
	return (0);
}
