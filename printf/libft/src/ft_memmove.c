/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 08:45:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/03 12:19:05 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char				*d;
	const char			*s;
	int					i;

	if (dst == NULL || src == NULL)
		return ((void *)dst);
	i = 0;
	d = dst;
	s = src;
	if (d >= s)
	{
		s = s + (len - 1);
		d = d + (len - 1);
	}
	while (len)
	{
		len--;
		d[i] = s[i];
		if (d < s)
			i++;
		else
			i--;
	}
	return (dst);
}
