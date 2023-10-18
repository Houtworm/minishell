/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker djonker@student.codam.nl             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 06:09:42 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:28 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_setzero(t_printf *strct)
{
	strct->left = 0;
	strct->zero = 0;
	strct->prec = 0;
	strct->widt = 0;
	strct->conv = '.';
	strct->leng = '.';
	strct->spac = 0;
	strct->plus = 0;
	strct->p = 0;
	strct->w = 0;
}

static int	ft_processtype2(t_printf *strct, va_list v)
{
	if (strct->type == 'd' || strct->type == 'i')
		ft_printf_proc_d(strct, va_arg(v, int));
	else if (strct->type == 'u')
		ft_printf_proc_u(strct, va_arg(v, unsigned int));
	else if (strct->type == 'x' || strct->type == 'X')
		ft_printf_proc_x(strct, va_arg(v, unsigned int));
	else if (strct->type == 'f' || strct->type == 'F')
		ft_printf_proc_f(strct, va_arg(v, double));
	else if (strct->type == 'e' || strct->type == 'E')
		ft_printf_proc_e(strct, va_arg(v, double));
	else if (strct->type == 'g' || strct->type == 'G')
		ft_printf_proc_g(strct, va_arg(v, double));
	else if (strct->type == 'a' || strct->type == 'A')
		ft_printf_proc_a(strct, va_arg(v, double));
	else if (strct->type == 'o')
		ft_printf_proc_o(strct, va_arg(v, unsigned int));
	else if (strct->type == 'b')
		ft_printf_proc_b(strct, va_arg(v, unsigned long long));
	return (0);
}

static int	ft_processtype(t_printf *strct, va_list v)
{
	int		*n;

	if (strct->type == 'S' || strct->type == 'C')
		strct->leng = 'l';
	if (strct->leng != '.')
		ft_processlength(strct, v);
	else if (strct->type == 'c')
		ft_printf_proc_c(strct, va_arg(v, int));
	else if (strct->type == 's')
		ft_printf_proc_s(strct, va_arg(v, char *));
	else if (strct->type == 'p')
		ft_printf_proc_p(strct, va_arg(v, unsigned long long));
	else if (strct->type == '%')
		ft_printf_proc_prec(strct, '%');
	else if (strct->type == 'n')
	{
		n = (int *)va_arg(v, int *);
		*n = strct->n;
	}
	else
		ft_processtype2(strct, v);
	return (0);
}

void	putcharform(t_printf *strct)
{
	ft_putchar(*strct->form);
	strct->n++;
	strct->form++;
}

int	ft_printf(const char *format, ...)
{
	va_list		v;
	t_printf	strct[1];

	if (!format)
		return (255);
	strct->form = (char *)format;
	strct->n = 0;
	va_start(v, format);
	while (*strct->form)
	{
		ft_setzero(strct);
		while (*strct->form != '%' && *strct->form)
			putcharform(strct);
		if (!*strct->form)
			break ;
		ft_processflag(strct, v);
		strct->type = *strct->form;
		ft_processtype(strct, v);
		strct->form++;
	}
	va_end(v);
	return (strct->n);
}
