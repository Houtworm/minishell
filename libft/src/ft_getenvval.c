/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_getenvval.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/17 02:40:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/04 03:39:39 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_getenvval(char **envp, char *var)
{
	char	*value;
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], temp, ft_strlen(temp)) == 0)
			break ;
	if (!envp[i])
	{
		free(temp);
		return (NULL);
	}
	value = ft_substr(envp[i], ft_strlen(temp), ft_strlen(envp[i]));
	free(temp);
	return (value);
}
