/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   complete.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/03 18:38:40 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 06:54:02 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_closeline(t_shell *shell)
{
	int		quote;
	char	*temp;
	int		ret;
	char	*gnl;

	quote = check_quote_closed(shell);
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
				temp = ft_vastrjoin(3, shell->line, "\n", gnl);
				free(gnl);
			}
			free(shell->line);
			shell->line = ft_strdup(temp);
		}
		temp = ft_vastrjoin(3, shell->line, "\n", gnl);
		free(gnl);
		free(shell->line);
		shell->line = ft_strdup(temp);
		free (temp);
		quote = check_quote_closed(shell);
	}
	return (shell->line);
}

char	*ft_completeline(t_shell *shell, int k)
{	
	char	*temp;
	int		ret;
	char	*gnl;
	int		i;

	i = 0;
	while (shell->line[i])
		i++;
	i--;
	while (shell->line[i] == ' ')
		i--;
	if (shell->line[i] != '&' && shell->line[i] != '|')
		return (shell->line);
	while ((shell->line[i] == '&' && shell->line[i - 1] == '&') || shell->line[i] == '|')
	{
		ft_putstr("> ");
		ret = get_next_line(0, &gnl);
		if (ret == 0)
			break;
		while (gnl[k])
			k++;
		while (gnl[k] == ' ')
			k--;
		temp = ft_strjoin(shell->line, gnl);
		free(gnl);
		free(shell->line);
		shell->line = ft_strdup(temp);
		free (temp);
		i += k;
	}
	return (shell->line);
}
