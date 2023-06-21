/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoh.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 03:00:29 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/05 20:33:06 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itoh(long double n)
{
	char		r[30];
	int			c;
	long double	tf;
	long long	ti;
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
