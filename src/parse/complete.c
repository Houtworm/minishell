/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   complete.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/03 18:38:40 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 11:43:40 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_closeline(t_shell *msh)
{
	int		quote;
	char	*temp;
	int		ret;
	char	*gnl;

	quote = check_quote_closed(msh);
	while (quote)
	{
		while (1)
		{
			if (quote)
				ft_putstr_fd("> ", 0);
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
				temp = ft_vastrjoin(3, msh->line, "\n", gnl);
				free(gnl);
			}
			free(msh->line);
			msh->line = ft_strdup(temp);
		}
		temp = ft_vastrjoin(3, msh->line, "\n", gnl);
		free(gnl);
		free(msh->line);
		msh->line = ft_strdup(temp);
		free (temp);
		quote = check_quote_closed(msh);
	}
	return (msh->line);
}

char	*ft_completeline(t_shell *msh, int k)
{
	char	*temp;
	int		ret;
	char	*gnl;
	int		i;

	i = 0;
	while (msh->line[i])
		i++;
	i--;
	while (msh->line[i] == ' ')
		i--;
	if (msh->line[i] != '&' && msh->line[i] != '|')
		return (msh->line);
	while ((msh->line[i] == '&' && msh->line[i - 1] == '&') || msh->line[i] == '|')
	{
		ft_putstr("> ");
		ret = get_next_line(0, &gnl);
		if (ret == 0)
			break;
		while (gnl[k])
			k++;
		while (gnl[k] == ' ')
			k--;
		temp = ft_strjoin(msh->line, gnl);
		free(gnl);
		free(msh->line);
		msh->line = ft_strdup(temp);
		free (temp);
		i += k;
	}
	return (msh->line);
}
