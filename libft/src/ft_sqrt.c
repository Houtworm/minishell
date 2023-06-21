/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 04:16:25 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:41:03 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned long long	ft_sqrt(unsigned long long n)
{
	unsigned long long	r;

	r = 0;
	while (r < 1000000000000000000 && r <= n / 2)
	{
		if (r * r == n)
			return (r);
		r++;
	}
	return (0);
}
