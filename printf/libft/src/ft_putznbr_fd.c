/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putznbr_fd.c                                    :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 04:22:10 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:47 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putznbr_fd(int n, int e, int fd)
{
	int	s;

	s = ft_intlen(n) - e;
	while (s != 0)
	{
		ft_putchar_fd('0', fd);
		s++;
	}
	ft_putnbr_fd(n, fd);
}
