/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_getpwd.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/17 02:40:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/17 02:55:28 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_getpwd(char **envp, int slash)
{
	char	*pwd;
	char	*temp;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			break ;
	if (!envp[i])
		return (NULL);
	temp = ft_substr(envp[i], 4, ft_strlen(envp[i]));
	if (!temp)
		return (NULL);
	if (slash)
		pwd = ft_strjoin(temp, "/");
	else
		pwd = ft_strjoin(temp, NULL);
	free(temp);
	return (pwd);
}