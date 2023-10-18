/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_proc_s.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/06 12:26:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:38 by houtworm      ########   odam.nl         */
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

static void	ft_preparation(t_printf *strct, char *r)
{
	if (strct->prec < 0)
		strct->p = 4;
	if (strct->prec < 0)
		strct->prec = 0;
	if (strct->widt < 0)
		strct->left = 1;
	if (strct->widt < 0 && strct->left == 1)
		strct->widt = strct->widt * -1;
	if (strct->plus == 5 && strct->p > 0 && strct->prec < 6)
		strct->widt = strct->widt;
	else if (strct->prec > 0 && strct->prec < (int)ft_strlen(r))
		strct->widt = strct->widt - strct->prec;
	else if ((strct->p > 0) && strct->p != 4 && strct->prec < (int)ft_strlen(r))
		strct->widt = strct->widt;
	else
		strct->widt = strct->widt - ft_strlen(r);
}

static void	ft_widthprecision(t_printf *strct)
{
	while (strct->widt > 0 && strct->left == 0)
		ft_putandcount(strct, ' ', 1);
}

static void	ft_valueleft(t_printf *strct, char *r)
{
	int	i;

	i = 0;
	if (strct->plus == 5 && strct->p > 0)
	{
		if (strct->prec < 6)
		{
			strct->prec = 0;
			strct->p = 2;
		}
	}
	if (strct->prec == 0 && strct->p != 2 && strct->p != 3)
	{
		ft_putstr(r);
		strct->n = strct->n + ft_strlen(r);
	}
	while (strct->prec > i && r[i])
	{
		ft_putchar(r[i]);
		strct->n++;
		i++;
	}
	while (strct->widt > 0)
		ft_putandcount(strct, ' ', 1);
}

void	ft_printf_proc_s(t_printf *strct, char *r)
{
	if (!r)
	{
		r = "(null)";
		strct->plus = 5;
		if (strct->prec < 0)
			strct->plus = 6;
	}
	ft_preparation(strct, r);
	ft_widthprecision(strct);
	ft_valueleft(strct, r);
}
