/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printf_proc_u.c                                 :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/06/06 12:26:37 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/07 01:21:37 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static void	ft_putandcount(t_printf *strct, char c, int w)
{
	ft_putchar(c);
	strct->n++;
	if (w == 1)
		strct->widt--;
	else if (w == 2)
		strct->prec--;
}

static void	ft_preparation(t_printf *strct, unsigned long long r)
{
	if (strct->widt < 0)
		strct->left = 1;
	if (strct->widt < 0 && strct->left == 1)
		strct->widt = strct->widt * -1;
	if (strct->prec < 0)
		strct->leng = 33;
	strct->prec = strct->prec - ft_luilen(r);
	if (strct->prec < 0)
		strct->prec = 0;
	strct->widt = strct->widt - (strct->prec + ft_luilen(r));
	if (strct->p > 0 && strct->zero == 0)
		strct->zero = 1;
	else if (strct->p > 0 && strct->zero == 2 && strct->leng == 46)
		strct->zero = 1;
}

static void	ft_widthprecision(t_printf *strct)
{
	while (strct->widt > 0 && strct->left == 0 && strct->zero < 2)
		ft_putandcount(strct, ' ', 1);
	while (strct->widt > 0 && strct->left == 0 && strct->zero > 0)
		ft_putandcount(strct, '0', 1);
	while (strct->prec > 0)
		ft_putandcount(strct, '0', 2);
}

static void	ft_valueleft(t_printf *strct, unsigned long long r)
{
	if (r != 0)
	{
		ft_putull(r);
		strct->n = strct->n + ft_luilen(r);
	}
	else if ((strct->p > 1 && strct->w != 1))
		strct->n = strct->n;
	else if (strct->p < 2)
		ft_putandcount(strct, '0', 0);
	else
		ft_putandcount(strct, ' ', 0);
	while (strct->widt > 0)
		ft_putandcount(strct, ' ', 1);
}

void	ft_printf_proc_u(t_printf *strct, unsigned long long r)
{
	ft_preparation(strct, r);
	ft_widthprecision(strct);
	ft_valueleft(strct, r);
}
