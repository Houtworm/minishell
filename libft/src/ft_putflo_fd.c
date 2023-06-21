/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putflo_fd.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 21:45:39 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:43 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putflo_fd(double n, int fd)
{
	int		i;
	int		f;

	i = n;
	f = ft_ftoi(n);
	ft_putnbr_fd(i, fd);
	ft_putchar_fd('.', fd);
	ft_putnbr_fd(f, fd);
}
