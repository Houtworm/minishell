/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 16:13:52 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/01 18:06:11 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*d;
	const char			*s;
	long unsigned int	i;

	if (!dst)
		return (dst);
	d = dst;
	if (!src)
	{
		*d = '\0';
		return (dst);
	}
	s = src;
	i = 0;
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
