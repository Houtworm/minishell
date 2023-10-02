/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/02 22:35:51 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	ft_parsepipe(char *line, t_shell shell)
{
	int	i;
	int	k;

	shell.line = ft_strdup(line);
	shell.forks = ft_calloc(ft_strlen(shell.line) * sizeof(t_forks), 1);
	i = 0;
	shell.forkamount = 0;
	while (shell.line[i])
	{
		k = 0;
		shell.forks[shell.forkamount].pipeline = ft_calloc(ft_strlen(shell.line) * 8, 1);
		while (!ft_strchr("|\"\'", shell.line[i]))
		{
			shell.forks[shell.forkamount].pipeline[k] = shell.line[i];
			i++;
			k++;
			if (shell.line[i] == '|' && shell.line[i + 1] == '|') 
			{
				shell.forks[shell.forkamount].pipeline[k] = shell.line[i];
				shell.forks[shell.forkamount].pipeline[k + 1] = shell.line[i + 1];
				i += 2;
				k += 2;
			}
		}
		if (shell.line[i] == '\"' || shell.line[i] == '\'')
		{
			ft_copyquote(&(shell.forks[shell.forkamount].pipeline), shell.line, k, i);
			k = ft_strlen(shell.forks[shell.forkamount].pipeline);
			i = ft_skipquote(shell.line, i) + 1;
			if (shell.line[i] == '\"' || shell.line[i] == '\'')
			{
				ft_copyquote(&(shell.forks[shell.forkamount].pipeline), shell.line, k, i);
				k = ft_strlen(shell.forks[shell.forkamount].pipeline);
				i = ft_skipquote(shell.line, i) + 1;
			}
			if (shell.line[i] == '|' && shell.line[i + 1] == '|') 
			{
				shell.forks[shell.forkamount].pipeline[k] = shell.line[i];
				shell.forks[shell.forkamount].pipeline[k + 1] = shell.line[i + 1];
				i += 2;
				k += 2;
			}
			while (shell.line[i] && shell.line[i] != '|')
			{
				shell.forks[shell.forkamount].pipeline[k] = shell.line[i];
				i++;
				k++;
				if (shell.line[i] == '|' && shell.line[i + 1] == '|') 
				{
					shell.forks[shell.forkamount].pipeline[k] = shell.line[i];
					shell.forks[shell.forkamount].pipeline[k + 1] = shell.line[i + 1];
					i += 2;
					k += 2;
				}
			}
		}
		shell.forks[shell.forkamount].pipeline[k] = '\0';
		if (shell.line[i] == '|'  && shell.line[i + 1] != '|')
		{
			i++;
			shell.forkamount++;		
		}
	}
	shell.forkamount++;	
	return (shell);
}
