/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_length.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 23:07:02 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:29 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_checkdi(t_printf *strct, va_list v)
{
	int	t;

	if (ft_chrstr(strct->type, "di") == 1)
	{
		if (ft_chrstr(strct->leng, "lqjtz"))
			ft_printf_proc_d(strct, va_arg(v, long long));
		if (strct->leng == 'h')
		{
			t = (short int)va_arg(v, int);
			ft_printf_proc_d(strct, t);
		}
		if (strct->leng == 'H')
		{
			t = (char)va_arg(v, int);
			ft_printf_proc_d(strct, t);
		}
	}
}

static void	ft_checku(t_printf *strct, va_list v)
{
	int	t;

	if (ft_chrstr(strct->type, "u") == 1)
	{
		if (ft_chrstr(strct->leng, "lqjtz"))
			ft_printf_proc_u(strct, va_arg(v, unsigned long long));
		if (strct->leng == 'h')
		{
			t = (unsigned short int)va_arg(v, int);
			ft_printf_proc_u(strct, t);
		}
		if (strct->leng == 'H')
		{
			t = (unsigned char)va_arg(v, int);
			ft_printf_proc_u(strct, t);
		}
	}
}

static void	ft_checko(t_printf *strct, va_list v)
{
	int	t;

	if (strct->type == 'o')
	{
		if (ft_chrstr(strct->leng, "lqjtz"))
			ft_printf_proc_o(strct, va_arg(v, unsigned long long));
		if (strct->leng == 'h')
		{
			t = (unsigned short int)va_arg(v, int);
			ft_printf_proc_o(strct, t);
		}
		if (strct->leng == 'H')
		{
			t = (unsigned char)va_arg(v, int);
			ft_printf_proc_o(strct, t);
		}
	}
}

static void	ft_checkxx(t_printf *strct, va_list v)
{
	int	t;

	if (ft_chrstr(strct->type, "xX") == 1)
	{
		if (ft_chrstr(strct->leng, "lqjtz"))
			ft_printf_proc_x(strct, va_arg(v, unsigned long long));
		if (strct->leng == 'h')
		{
			t = (unsigned short int)va_arg(v, int);
			ft_printf_proc_x(strct, t);
		}
		if (strct->leng == 'H')
		{
			t = (unsigned char)va_arg(v, int);
			ft_printf_proc_x(strct, t);
		}
	}
}

void	ft_processlength(t_printf *strct, va_list v)
{
	ft_checkdi(strct, v);
	ft_checku(strct, v);
	ft_checko(strct, v);
	ft_checkxx(strct, v);
	if (ft_chrstr(strct->type, "fF") && strct->leng == 'L')
		ft_printf_proc_f(strct, va_arg(v, long double));
	if (ft_chrstr(strct->type, "eE") && strct->leng == 'L')
		ft_printf_proc_f(strct, va_arg(v, long double));
	if (ft_chrstr(strct->type, "gG") && strct->leng == 'L')
		ft_printf_proc_f(strct, va_arg(v, long double));
	if (ft_chrstr(strct->type, "aA") && strct->leng == 'L')
		ft_printf_proc_f(strct, va_arg(v, long double));
	strct->leng = '.';
}
