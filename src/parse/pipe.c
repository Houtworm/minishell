/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/13 02:19:34 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*ft_parsepipe(t_shell *shell)
{
	int	i;
	int	k;

	shell->forks = ft_calloc(200, 16);
	i = 0;
	shell->forkamount = 0;
	while (shell->line[i])
	{
		k = 0;
		shell->forks[shell->forkamount].pipeline = ft_calloc(ft_strlen(shell->line) * 8, 1);
		while (!ft_strchr("|\"\'", shell->line[i]))
		{
			shell->forks[shell->forkamount].pipeline[k] = shell->line[i];
			i++;
			k++;
			if (shell->line[i] == '|' && shell->line[i + 1] == '|') 
			{
				shell->forks[shell->forkamount].pipeline[k] = shell->line[i];
				shell->forks[shell->forkamount].pipeline[k + 1] = shell->line[i + 1];
				i += 2;
				k += 2;
			}
		}
		if (shell->line[i] == '\"' || shell->line[i] == '\'')
		{
			ft_copyquote(&(shell->forks[shell->forkamount].pipeline), shell->line, k, i);
			k = ft_strlen(shell->forks[shell->forkamount].pipeline);
			i = ft_skipquote(shell->line, i) + 1;
			if (shell->line[i] == '\"' || shell->line[i] == '\'')
			{
				ft_copyquote(&(shell->forks[shell->forkamount].pipeline), shell->line, k, i);
				k = ft_strlen(shell->forks[shell->forkamount].pipeline);
				i = ft_skipquote(shell->line, i) + 1;
			}
			if (shell->line[i] == '|' && shell->line[i + 1] == '|') 
			{
				shell->forks[shell->forkamount].pipeline[k] = shell->line[i];
				shell->forks[shell->forkamount].pipeline[k + 1] = shell->line[i + 1];
				i += 2;
				k += 2;
			}
			while (shell->line[i] && shell->line[i] != '|')
			{
				shell->forks[shell->forkamount].pipeline[k] = shell->line[i];
				i++;
				k++;
				if (shell->line[i] == '|' && shell->line[i + 1] == '|') 
				{
					shell->forks[shell->forkamount].pipeline[k] = shell->line[i];
					shell->forks[shell->forkamount].pipeline[k + 1] = shell->line[i + 1];
					i += 2;
					k += 2;
				}
			}
		}
		shell->forks[shell->forkamount].pipeline[k] = '\0';
		if (shell->line[i] == '|'  && shell->line[i + 1] != '|')
		{
			i++;
			shell->forkamount++;		
		}
	}
	shell->forkamount++;	
	return (shell);
}
