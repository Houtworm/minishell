/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_proc_a.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/06 12:26:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:35 by houtworm      ########   odam.nl         */
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

static void	ft_preparation(t_printf *strct, long double r)
{
	if (strct->widt < 0)
		strct->left = 1;
	if (strct->widt < 0 && strct->left == 1)
		strct->widt = strct->widt * -1;
	if (strct->prec < 0)
		strct->prec = 0;
	if (strct->spac == 1 && r >= 0)
		ft_putandcount(strct, ' ', 1);
	if (strct->p == 1 && strct->prec > 0)
		strct->widt = strct->widt - (strct->prec + 1 + ft_intlen(r));
	else if (strct->prec == 0 && strct->p > 1)
		strct->widt = strct->widt - ft_intlen(r);
	else
		strct->widt = strct->widt - (7 + ft_intlen(r));
	if (strct->plus == 1 && r >= 0)
		strct->widt--;
	if (strct->p > 0)
		strct->zero = 1;
}

static void	ft_widthprecision(t_printf *strct, long double r)
{
	while (strct->widt > 0 && strct->left == 0 && strct->zero < 2)
		ft_putandcount(strct, ' ', 1);
	if (strct->plus > 0 && r >= 0 && strct->zero > 0)
		ft_putandcount(strct, '+', 0);
	if (strct->zero > 0 && r < 0)
		ft_putandcount(strct, '-', 0);
	while (strct->widt > 0 && strct->left == 0 && strct->zero == 2)
		ft_putandcount(strct, '0', 1);
	if (r < 0 && strct->zero == 0)
		ft_putandcount(strct, '-', 0);
	if (strct->plus > 0 && r >= 0 && strct->zero == 0)
		ft_putandcount(strct, '+', 1);
}

static void	ft_valueleft(t_printf *strct, long double r)
{
	int	cap;

	cap = 0;
	if (r < 0)
		r = r * -1;
	if (strct->type == 'A')
	{
		cap++;
		ft_putstr("0X");
	}
	else
		ft_putstr("0x");
	if (strct->p > 0)
	{
		ft_putzscih(r, strct->prec, cap);
		strct->n = strct->n + strct->prec + 8;
	}
	else
	{
		ft_putzscih(r, 20, cap);
		strct->n = strct->n + 13;
	}
	while (strct->widt > 0)
		ft_putandcount(strct, ' ', 1);
}

void	ft_printf_proc_a(t_printf *strct, long double r)
{
	if (r != r)
		ft_printf_proc_inf(strct, "nan", 1);
	else if (r > 0 && r / r != r / r)
		ft_printf_proc_inf(strct, "inf", 1);
	else if (r < 0 && r / r != r / r)
		ft_printf_proc_inf(strct, "inf", 0);
	else
	{
		ft_preparation(strct, r);
		ft_widthprecision(strct, r);
		ft_valueleft(strct, r);
	}
}
