/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_strchr.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/11/22 13:34:05 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 06:08:13 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (c == *s)
			return ((char *)s);
		s++;
	}
	if (c == *s)
		return ((char *)s);
	return (0);
}
