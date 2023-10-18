/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_proc_c.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/06 12:26:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:40 by houtworm      ########   odam.nl         */
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
