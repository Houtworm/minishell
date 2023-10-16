/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   hashtag.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 21:08:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 11:44:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsehashtag(t_shell *msh)
{
	char	*temp;
	int		i;

	if (ft_checkoutquote(msh->line, '#', 2) >= 0)
	{
		i = 0;
		if (msh->line[0] == '#')
		{
			msh->line[0] = '\0';
			return (msh->line);
		}
		while (msh->line[i] && (msh->line[i] != ' ' || msh->line[i + 1] != '#'))
		{
			if (msh->line[i] == '\'')
			{
				i++;
				while (msh->line[i] != '\'')
					i++;
			}
			if (msh->line[i] == '\"')
			{
				i++;
				while (msh->line[i] != '\"')
					i++;
			}
			i++;
		}
		temp = ft_substr(msh->line, 0, i);
		free(msh->line);
		msh->line = ft_strdup(temp);
		free(temp);
	}
	return (msh->line);
}
