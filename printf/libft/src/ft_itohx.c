/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itohx.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 03:00:29 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:09 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itohx(long double n)
{
	char		r[30];
	long int	c;
	long double	tf;
	long int	ti;
	char		*s;

	c = 0;
	while (n != 0)
	{
		if (n < 16)
			r[c] = ft_htod(n);
		else if (n > 15)
		{
			tf = n / 16;
			ti = n / 16;
			tf = (tf - ti) * 16;
			r[c] = ft_htod(tf);
		}
		ti = n / 16;
		n = ti;
		c++;
	}
	r[c] = '\0';
	s = ft_revstr(r);
	return (s);
}
