/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printf_proc_c.c                                 :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/06/06 12:26:37 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/07 01:21:36 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static void	ft_putandcount(t_printf *strct, char c, int w)
{
	ft_putchar(c);
	strct->n++;
	if (w == 1)
		strct->widt--;
}

static void	ft_preparation(t_printf *strct, char r)
{
	if (strct->widt < 0)
		strct->left = 1;
	if (strct->widt < 0 && strct->left == 1)
		strct->widt = strct->widt * -1;
	if (r || strct->p != 3 || r == 0)
		strct->widt--;
}

static void	ft_widthvalue(t_printf *strct, char r)
{
	while (strct->widt > 0 && strct->left == 0)
		ft_putandcount(strct, ' ', 1);
	ft_putchar(r);
	strct->n++;
	while (strct->widt > 0)
		ft_putandcount(strct, ' ', 1);
}

void	ft_printf_proc_c(t_printf *strct, char r)
{
	ft_preparation(strct, r);
	ft_widthvalue(strct, r);
}
