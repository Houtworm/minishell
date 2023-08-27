/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   variable.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/27 12:21:13 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parsevariable(t_cmds cmd)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	while (ft_checkoutquote(cmd.pipeline, '*', 2))
	{
		i = 0;
		begin = ft_calloc((ft_strlen(cmd.pipeline) + 1) * 8, 1);
		var = ft_calloc((ft_strlen(cmd.pipeline) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(cmd.pipeline) + 1) * 8, 1);
		while (cmd.pipeline[i])
		{
			j = 0;
			while (cmd.pipeline[i] && cmd.pipeline[i] != '$')
			{
				begin[j] = cmd.pipeline[i];
				i++;
				j++;
			}
			if (cmd.pipeline[i] == '$')
				i++;
			j = 0;
			while ((cmd.pipeline[i] >= 'A' && cmd.pipeline[i] <= 'Z') || (cmd.pipeline[i] >= 'a' && cmd.pipeline[i] <= 'z' ) || cmd.pipeline[i] == '_')
			{
				var[j] = cmd.pipeline[i];
				i++;
				j++;
			}
			val = ft_getenvval(cmd.envp, var);
			j = 0;
			while (cmd.pipeline[i])
			{
				rest[j] = cmd.pipeline[i];
				i++;
				j++;
			}
			cmd.pipeline = ft_vastrjoin(3, begin, val, rest);
			ft_vafree(4, begin, var, val, rest);
		}
	}
	return (0);
}
