/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_flags.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/11 19:30:29 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:28 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_getnumber(t_printf *strct)
{
	char	r[12];
	int		i;

	i = 0;
	while (ft_isdigit(*strct->form))
	{
		r[i] = *strct->form;
		strct->form++;
		i++;
	}
	r[i] = '\0';
	if (*r)
		return (ft_atoi(r));
	return (0);
}

static void	ft_precision(t_printf *strct, va_list v)
{
	strct->form++;
	strct->p = 1;
	if (*strct->form == '*')
	{
		strct->prec = va_arg(v, int);
		if (strct->prec == 0)
			strct->p = 3;
		strct->form++;
	}
	else if (ft_isdigit(*strct->form))
	{
		strct->prec = ft_getnumber(strct);
		if (strct->prec == 0)
			strct->p = 3;
	}
	else
		strct->p = 2;
}

static void	ft_fieldwidth(t_printf *strct, va_list v)
{
	strct->w = 1;
	if (*strct->form == '*')
	{
		strct->widt = va_arg(v, int);
		if (strct->widt == 0)
			strct->w = 3;
		strct->form++;
	}
	else
	{
		strct->widt = ft_getnumber(strct);
		if (strct->widt == 0)
			strct->w = 3;
	}
}

static void	ft_lengthspec(t_printf *strct)
{
	if (*strct->form == 'h' && strct->form[1] == 'h')
	{
		strct->leng = 'H';
		strct->form++;
	}
	else if (*strct->form == 'l' && strct->form[1] == 'l')
	{
		strct->leng = 'q';
		strct->form++;
	}
	else
		strct->leng = *strct->form;
}

void	ft_processflag(t_printf *strct, va_list v)
{
	while (strct->form[1])
	{
		strct->form++;
		if (*strct->form == '+')
			strct->plus = 1;
		if ((*strct->form > '0' && *strct->form <= '9') || *strct->form == '*')
			ft_fieldwidth(strct, v);
		if (*strct->form == '.')
			ft_precision(strct, v);
		if (*strct->form == '0')
			strct->zero = 2;
		if (*strct->form == '-')
			strct->left = 2;
		if (*strct->form == '#')
			strct->conv = 1;
		if (*strct->form == ' ')
			strct->spac = 1;
		if (ft_chrstr(*strct->form, "lhLqtjz") == 1)
			ft_lengthspec(strct);
		if (ft_chrstr(*strct->form, "cspdiuxXnfgeoGFEaACSb%") == 1)
			break ;
	}
}
