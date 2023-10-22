/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/22 03:13:07 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsevar_rest(char *line, char *dst, int *i, int rest)
{
	int	j;

	j = 0;
	while (!rest && ((line[*i] >= 'A' && line[*i] <= 'Z')
			|| (line[*i] >= 'a' && line[*i] <= 'z' ) || line[*i] == '_'))
	{
		dst[j] = line[*i];
		(*i)++;
		j++;
	}
	while (rest && line[*i])
	{
		dst[j] = line[*i];
		(*i)++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_parsevarval(t_shell msh, char *line, char **var, int *i)
{
	char	*val;

	if (line[*i] == '?')
	{
		val = ft_itoa(msh.code % 256);
		(*i)++;
	}
	else if (line[*i] == '$')
	{
		val = ft_itoa(msh.pid);
		(*i)++;
	}
	else if (line[*i] == ' ')
	{
		val = ft_strdup("$");
		(*i)++;
	}
	else if (!line[*i])
		val = ft_strdup("$");
	else
	{
		*var = ft_parsevar_rest(line, *var, i, 0);
		val = ft_getenvval(msh.envp, *var);
	}
	return (val);
}

char	*ft_parsevar(char *line, t_shell msh, int quote)
{
	int		i;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	while (ft_checkoutquotevar(line, 0) >= 0)
	{
		i = 0;
		begin = ft_parsebegin(line, begin, quote, &i);
		val = ft_parsevarval(msh, line, &var, &i);
		rest = ft_parsevar_rest(line, rest, &i, 1);
		free (line);
		line = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (line);
}
