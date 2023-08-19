/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/19 17:33:02 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strct_per_cmd(char **cmd, t_shell *shell)
{
	int	i;
	char	**tmp;
	t_forks	*forks;

	i = 0;
	while (cmd[i])
	{
		tmp = ft_split(cmd[i], '|');
		while (tmp)
		{
			//how should I create struct per command separated by semicolon?
		}
		ft_frearr(tmp);
		i++;
	}
}