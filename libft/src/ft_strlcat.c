/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 09:55:53 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/03 13:56:46 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dl;
	size_t	sl;
	size_t	r;

	dl = ft_strlen(dst);
	r = ft_strlen((char *)src);
	sl = 0;
	if (dstsize == 0)
		return (r);
	if (!src)
		return (dl);
	if (dstsize < dl)
		r = r + dstsize;
	else
		r = r + dl;
	while (src[sl] != '\0' && dl < dstsize - 1)
	{
		dst[dl] = src[sl];
		sl++;
		dl++;
	}
	if (dl < dstsize)
		dst[dl] = '\0';
	return (r);
}
