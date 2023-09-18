/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_cpptostr.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/18 12:17:01 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/18 12:18:39 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_cpptostr(char **cpp)
{
	int	i;
	char	*ret;
	char	*temp;
	char	*temp2;

	i = 1;
	if (cpp[0])
		temp2 = ft_strdup(cpp[0]);
	while (cpp[i])
	{
		temp = ft_strjoin(temp2, cpp[i]);
		free(temp2);
		temp2 = ft_strdup(temp);
		free(temp);
		i++;
	}
	ret = ft_strdup(temp2);
	free(temp2);
	return (ret);
}
