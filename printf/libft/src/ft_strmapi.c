/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 03:04:33 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:41:11 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*r;

	i = 0;
	if (f == NULL || s == NULL)
		return (0x0);
	r = (char *)malloc(sizeof(char) * (ft_strlen((char *)s)) + 1);
	if (r == NULL)
		return (r);
	while (s[i] != '\0')
	{
		r[i] = f(i, s[i]);
		i++;
	}
	r[i] = '\0';
	return (r);
}
