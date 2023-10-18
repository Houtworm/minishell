/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:14 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsevariable(char *line, t_shell msh, int quote)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	while (ft_checkoutquotevar(line) >= 0)
	{
		i = 0;
		j = 0;
		while (line[i] && line[i] != '$')
		{
			if (quote && line[i] == '\'')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\'')
				{
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			if (quote && line[i] == '\"')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\"')
				{
					if (line[i] == '$' && line[i + 1] != '\'' && line[i + 1] != '\"' && line[i + 1] != '(')
						break ;
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			if (!line[i] || (line[i] == '$' && line[i + 1] != '\'' && line[i + 1] != '\"' && line[i + 1] != '('))
				break ;
			begin[j] = line[i];
			i++;
			j++;
			if (line[i] == '$' && line[i + 1] == '(')
			{
				while (line[i] != ')')
				{
					begin[j] = line[i];
					j++;
					i++;
				}
				begin[j] = line[i];
				i++;
				j++;
			}
		}
		if (line[i] == '$')
		{
			begin[j] = '\0';
			i++;
		}
		if (line[i] == '?')
		{
			val = ft_itoa(msh.code % 256);
			i++;
		}
		else if (line[i] == '$')
		{
			val = ft_itoa(msh.pid);
			i++;
		}
		else if (line[i] == ' ')
		{
			val = ft_strdup("$");
			i++;
		}
		else if (!line[i])
			val = ft_strdup("$");
		else
		{
			j = 0;
			while ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z' ) || line[i] == '_')
			{
				var[j] = line[i];
				i++;
				j++;
			}
			var[j] = '\0';
			val = ft_getenvval(msh.envp, var);
		}
		j = 0;
		while (line[i])
		{
			rest[j] = line[i];
			i++;
			j++;
		}
		rest[j] = '\0';
		free (line);
		line = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (line);
}
