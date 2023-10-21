/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 19:57:43 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/22 01:39:55 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_quoteinvariable(char *line, char *begin, int *i, int *j)
{
	begin[*j] = line[*i];
	(*i)++;
	(*j)++;
	if (line[(*i) - 1] == '\'')
	{
		while (line[*i] && line[*i] != '\'')
		{
			begin[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (line[(*i) - 1] == '\"')
	{
		while (line[*i] && line[*i] != '\"')
		{
			if (line[*i] == '$' && line[(*i) + 1] != '\''
				&& line[*i + 1] != '\"' && line[*i + 1] != '(')
				break ;
			begin[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
	}
	return (begin);
}

char	*ft_cpnonvariable(char *line, char *begin, int *i, int *j)
{
	begin[*j] = line[*i];
	(*i)++;
	(*j)++;
	if (line[*i] == '$' && line[(*i) + 1] == '(')
	{
		while (line[*i] != ')')
		{
			begin[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
		begin[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	return (begin);
}

char	*ft_parsebegin(char *line, char *begin, int quote, int *i)
{
	int		j;

	j = 0;
	while (line[*i] && line[*i] != '$')
	{
		if (quote && (line[*i] == '\'' || line[*i] == '\"'))
			begin = ft_quoteinvariable(line, begin, i, &j);
		if (!line[*i] || (line[*i] == '$' && line[*i + 1] != '\''
				&& line[*i + 1] != '\"' && line[*i + 1] != '('))
			break ;
		begin = ft_cpnonvariable(line, begin, i, &j);
	}
	if (line[*i] == '$')
	{
		begin[j] = '\0';
		(*i)++;
	}
	return (begin);
}
