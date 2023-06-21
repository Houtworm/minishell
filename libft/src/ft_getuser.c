/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_getuser.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/17 02:40:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/17 02:55:28 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_getuser(char **envp)
{
	char	*user;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "USER=", 5) == 0)
			break ;
	if (!envp[i])
		return (NULL);
	user = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (user);
}
