/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putflo.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 21:45:39 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:43 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putflo(double n)
{
	int		i;
	int		f;

	i = n;
	f = ft_ftoi(n);
	ft_putnbr(i);
	ft_putchar('.');
	ft_putnbr(f);
}
