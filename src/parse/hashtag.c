/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   hashtag.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 21:08:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 01:18:42 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsehashtag(t_shell *shell)
{
	char	*temp;
	int		i;

	if (ft_checkoutquote(shell->line, '#', 2) >= 0)
	{
		i = 0;
		if (shell->line[0] == '#')
		{
			shell->line[0] = '\0';
			return (shell->line);
		}
		while (shell->line[i] && (shell->line[i] != ' ' || shell->line[i + 1] != '#'))
		{
			if (shell->line[i] == '\'')
			{
				i++;
				while (shell->line[i] != '\'')
					i++;
			}
			if (shell->line[i] == '\"')
			{
				i++;
				while (shell->line[i] != '\"')
					i++;
			}
			i++;
		}
		temp = ft_substr(shell->line, 0, i);
		free(shell->line);
		shell->line = ft_strdup(temp);
		free(temp);
	}
	return (shell->line);
}
