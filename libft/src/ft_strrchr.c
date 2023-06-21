/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 16:14:50 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/03 14:52:43 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	if (!s)
		return (NULL);
	p = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			p = (char *)s;
		s++;
	}
	return (p);
}
