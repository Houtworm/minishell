/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_printf_proc_x.c                                 :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/06/06 12:26:37 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/07 01:21:38 by houtworm         ###   ########.fr       */
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
	if (r > 0)
		strct->temp = ft_itoh(r);
	if (r == 0)
		strct->temp = "0";
	if (strct->widt < 0)
		strct->left = 1;
	if (strct->widt < 0 && strct->left == 1)
		strct->widt = strct->widt * -1;
	if (strct->prec < 0)
		strct->leng = 33;
	strct->prec = strct->prec - ft_strlen(strct->temp);
	if (strct->prec < 0)
		strct->prec = 0;
	strct->widt = strct->widt - (strct->prec + ft_strlen(strct->temp));
	if (strct->p > 0 && strct->zero == 0)
		strct->zero = 1;
	else if (strct->p > 0 && strct->zero == 2 && strct->leng == 46)
		strct->zero = 1;
	if (strct->conv == 1 && r > 0)
		strct->widt = strct->widt - 2;
}

static void	ft_widthprecision(t_printf *strct, unsigned long long r)
{
	while (strct->widt > 0 && strct->left == 0 && strct->zero < 2)
		ft_putandcount(strct, ' ', 1);
	if (strct->conv == 1 && strct->zero > 0 && r > 0)
	{
		ft_putandcount(strct, '0', 0);
		ft_putandcount(strct, strct->type, 0);
	}
	while (strct->widt > 0 && strct->left == 0 && strct->zero == 2)
		ft_putandcount(strct, '0', 1);
	while (strct->prec > 0)
		ft_putandcount(strct, '0', 2);
	if (strct->conv == 1 && strct->zero == 0 && r > 0)
	{
		ft_putandcount(strct, '0', 0);
		ft_putandcount(strct, strct->type, 0);
	}
}

static void	ft_valueleft(t_printf *strct)
{
	if (ft_strncmp(strct->temp, "0", 2))
	{
		if (strct->type == 'X')
			strct->temp = ft_strupp(strct->temp);
		ft_putstr(strct->temp);
		strct->n = strct->n + ft_strlen(strct->temp);
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

void	ft_printf_proc_x(t_printf *strct, unsigned long long r)
{
	ft_preparation(strct, r);
	ft_widthprecision(strct, r);
	ft_valueleft(strct);
}
