/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   hashtag.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 21:08:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/18 04:20:18 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_gethashtagpos(t_shell *msh)
{
	int	i;

	i = 0;
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
	return (i);
}

char	*ft_parsehashtag(t_shell *msh)
{
	char	*temp;
	int		i;

	if (ft_checkoutquote(msh->line, '#', 2) >= 0)
	{
		if (msh->line[0] == '#')
		{
			msh->line[0] = '\0';
			return (msh->line);
		}
		i = ft_gethashtagpos(msh);
		temp = ft_substr(msh->line, 0, i);
		free(msh->line);
		msh->line = ft_strdup(temp);
		free(temp);
	}
	return (msh->line);
}
