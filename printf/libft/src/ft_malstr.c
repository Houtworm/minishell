/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_malstr.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 15:21:11 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:36 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_malstr(char *s, char c)
{
	char	*r;
	int		l;

	r = ft_calloc(ft_wrdlen((char *)s, c, 0) + 1, 1);
	if (!r)
		return (NULL);
	l = 0;
	while (*s != '\0' && *s != c)
	{
		r[l] = *s;
		l++;
		s++;
	}
	return (r);
}
