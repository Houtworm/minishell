/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 07:28:50 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/03 04:52:34 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

typedef struct s_printf
{
	char		*form;
	char		type;
	int			leng;
	int			left;
	int			zero;
	int			prec;
	int			widt;
	int			conv;
	int			spac;
	int			plus;
	char		*temp;
	int			n;
	int			w;
	int			p;
}	t_printf;

int				ft_printf(const char *format, ...);
void			ft_processflag(t_printf *strct, va_list v);
void			ft_processlength(t_printf *strct, va_list v);
void			ft_printf_proc_c(t_printf *strct, char r);
void			ft_printf_proc_s(t_printf *strct, char *r);
void			ft_printf_proc_p(t_printf *strct, unsigned long long r);
void			ft_printf_proc_d(t_printf *strct, long long r);
void			ft_printf_proc_u(t_printf *strct, unsigned long long r);
void			ft_printf_proc_x(t_printf *strct, unsigned long long r);
void			ft_printf_proc_n(t_printf *strct, unsigned long long r);
void			ft_printf_proc_f(t_printf *strct, long double r);
void			ft_printf_proc_g(t_printf *strct, long double r);
void			ft_printf_proc_e(t_printf *strct, long double r);
void			ft_printf_proc_o(t_printf *strct, unsigned long long r);
void			ft_printf_proc_a(t_printf *strct, long double r);
void			ft_printf_proc_b(t_printf *strct, unsigned long long r);
void			ft_printf_proc_inf(t_printf *strct, char *r, int sign);
void			ft_printf_proc_prec(t_printf *strct, char r);

#endif
