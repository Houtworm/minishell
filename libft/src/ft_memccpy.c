/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 08:38:54 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/24 20:52:37 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*d;
	unsigned const char		*s;
	unsigned char			u;

	if (!dst || !src)
		return (NULL);
	if (u > ft_strlen(dst))
		u = ft_strlen(dst);
	d = dst;
	s = src;
	u = c;
	while (n != 0)
	{
		*d = *s;
		if (*d == u)
			return (d + 1);
		n--;
		d++;
		s++;
	}
	return (NULL);
}
