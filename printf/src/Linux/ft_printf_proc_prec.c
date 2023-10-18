/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_proc_prec.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/06 12:26:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:38 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

void	ft_printf_proc_prec(t_printf *strct, char r)
{
	ft_putchar('%');
	strct->n++;
}
