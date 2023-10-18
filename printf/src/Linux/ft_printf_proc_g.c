/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_proc_g.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/06 12:26:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:37 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static void	ft_withprecision(t_printf *strct, long double r, int lenght)
{
	if (strct->prec == lenght)
	{
		strct->prec = lenght;
		ft_printf_proc_d(strct, r);
	}
	else if (lenght < strct->prec)
	{
		strct->prec = strct->prec - lenght;
		ft_printf_proc_f(strct, r);
	}
	else if (lenght > strct->prec)
	{
		strct->prec = strct->prec - 1;
		ft_printf_proc_e(strct, r);
	}
	else if (lenght > 6)
	{
		strct->prec = strct->prec + 5 - lenght;
		ft_printf_proc_e(strct, r);
	}
	else
	{
		strct->prec = strct->prec + 5 - lenght;
		ft_printf_proc_f(strct, r);
	}
}

static void	ft_noprecision(t_printf *strct, long double r, int lenght)
{
	if (lenght > 6)
	{
		strct->p = 1;
		strct->prec = 5;
		ft_printf_proc_e(strct, r);
	}
	else
	{
		strct->prec = 6 - lenght;
		strct->p = 1;
		if (strct->prec <= 0)
			strct->p = 2;
		ft_printf_proc_f(strct, r);
	}
}

void	ft_printf_proc_g(t_printf *strct, long double r)
{
	int	lenght;

	if (r != r)
		ft_printf_proc_inf(strct, "nan", 1);
	else if (r > 0 && r / r != r / r)
		ft_printf_proc_inf(strct, "inf", 1);
	else if (r < 0 && r / r != r / r)
		ft_printf_proc_inf(strct, "inf", 0);
	else
	{
		lenght = ft_intlen(r);
		if (r < 0)
			lenght--;
		if (r == 0.0)
		{
			strct->prec = 1;
			ft_printf_proc_d(strct, 0);
		}
		else if (strct->p > 0)
			ft_withprecision(strct, r, lenght);
		else
			ft_noprecision(strct, r, lenght);
	}
}
