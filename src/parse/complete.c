/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 18:38:40 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/25 04:55:48 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_closelastline(t_shell *msh, char *gnl, char *temp)
{
	temp = ft_vastrjoin(3, msh->line, "\n", gnl);
	ft_vafree(2, msh->line, gnl);
	msh->line = ft_strdup(temp);
	free (temp);
	return (check_quote_closed(msh));
}

char	*ft_closeline(t_shell *msh, int quote, char *temp)
{
	int		ret;
	char	*gnl;

	while (quote)
	{
		while (1)
		{
			if (quote)
				ft_putstr_fd("> ", 0);
			ret = get_next_line(0, &gnl);
			if (ret == 0 || (quote == '\'' && ft_strchr(gnl, '\''))
				|| (quote == '\"' && ft_strchr(gnl, '\"'))
				|| (quote == '`' && ft_strchr(gnl, '`'))
				|| (quote == '(' && ft_strchr(gnl, ')')))
				break ;
			temp = ft_vastrjoin(3, msh->line, "\n", gnl);
			free(gnl);
			free(msh->line);
			msh->line = ft_strdup(temp);
			free(temp);
		}
		quote = ft_closelastline(msh, gnl, temp);
	}
	return (msh->line);
}

char	*ft_completeline(t_shell *msh, int i, char *temp)
{
	int		ret;
	char	*gnl;
	int		k;

	k = 0;
	if (msh->line[i] != '&' && msh->line[i] != '|')
		return (msh->line);
	while ((msh->line[i] == '&' && msh->line[i - 1] == '&')
		|| msh->line[i] == '|')
	{
		ft_putstr("> ");
		ret = get_next_line(0, &gnl);
		if (ret == 0)
			break ;
		while (gnl[k])
			k++;
		while (gnl[k] == ' ')
			k--;
		temp = ft_strjoin(msh->line, gnl);
		ft_vafree(2, msh->line, gnl);
		msh->line = ft_strdup(temp);
		free (temp);
		i += k;
	}
	return (msh->line);
}

void	ft_close_completeline(t_shell *msh)
{
	int	i;

	i = 0;
	if (ft_isallbyte(msh->line, ' '))
		return ;
	while (msh->line[i])
		i++;
	i--;
	while (msh->line[i] == ' ')
		i--;
	ft_completeline(msh, i, NULL);
	while (check_quote_closed(msh))
	{
		ft_closeline(msh, check_quote_closed(msh), NULL);
		while (msh->line[i])
			i++;
		i--;
		while (msh->line[i] == ' ')
			i--;
		ft_completeline(msh, i, NULL);
	}
}
