/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fczero.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 04:29:09 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:38:49 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_fczero(long double n)
{
	long double	f;
	long long	i;
	int			l;

	l = 0;
	i = n;
	f = n - i;
	f = f * 10;
	while (f < 1)
	{
		l++;
		n = n * 10;
		i = n;
		f = n - i;
		f = f * 10;
	}
	return (l);
}
