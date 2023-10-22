/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 02:58:42 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/22 04:28:33 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_cpnonquote(char *args, char *new, int *j, int *k)
{
	char	quote;

	if (args[*j] && args[*j] != '\'' && args[*j] != '\"')
	{
		new[*k] = args[*j];
		(*j)++;
		(*k)++;
	}
	if (args[*j] == '\'' || args[*j] == '\"')
	{
		quote = args[*j];
		(*j)++;
		while (args[*j] && args[*j] != quote)
		{
			new[*k] = args[*j];
			(*j)++;
			(*k)++;
		}
		(*j)++;
	}
	return (new);
}

char	*ft_cpwithquote(char *cmd, char *arg, int *icmd, int *iarg)
{
	char	quote;

	if (cmd[*icmd] == '\'' || cmd[*icmd] == '\"')
	{
		arg[*iarg] = cmd[*icmd];
		quote = cmd[*icmd];
		(*iarg)++;
		(*icmd)++;
		while (cmd[*icmd] && cmd[*icmd] != quote)
		{
			arg[*iarg] = cmd[*icmd];
			(*iarg)++;
			(*icmd)++;
		}
	}
	if (cmd[*icmd])
	{
		arg[*iarg] = cmd[*icmd];
		(*iarg)++;
		(*icmd)++;
	}
	return (arg);
}

char	**ft_removequotes(char **args)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (args[i])
		i++;
	new = ft_calloc(i + 2, 8);
	i = 0;
	while (args[i])
	{
		new[i] = ft_calloc(1000, 8);
		j = 0;
		k = 0;
		while (args[i][j])
			new[i] = ft_cpnonquote(args[i], new[i], &j, &k);
		new[i][k] = '\0';
		i++;
	}
	ft_frearr(args);
	new[i] = NULL;
	new[i + 1] = NULL;
	return (new);
}
