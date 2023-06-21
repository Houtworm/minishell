/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/08/04 06:48:59 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/07 00:40:44 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_base(unsigned long long number, int base)
{
	if (number >= (unsigned long long)base)
		ft_putnbr_base(number / base, base);
	number %= base;
	if (number >= 10)
		number = number + 87;
	else
		number = number + 48;
	ft_putchar(number);
}
