/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_gethome.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/17 02:40:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/24 19:03:02 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gethome(char **envp)
{
	char	*home;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			break ;
	if (!envp[i])
		return (NULL);
	home = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (home);
}
