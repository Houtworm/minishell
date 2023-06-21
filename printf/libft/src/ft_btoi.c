/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 13:44:56 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:36:46 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_btoi(int i, int e)
{
	char	*s;
	int		is;
	int		it;
	int		d;
	int		r;

	d = ft_intlen(i);
	it = 128;
	is = 0;
	r = 0;
	while (d < e)
	{
		it = it / 2;
		d++;
	}
	s = ft_itoa(i);
	while (s[is] != '\0')
	{
		if (s[is] == '1')
			r = r + it;
		it = it / 2;
		is++;
	}
	free(s);
	return (r);
}
