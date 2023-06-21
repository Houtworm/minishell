/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intrchr.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 16:14:50 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/20 14:48:22 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intrchr(const char *s, int c)
{
	int		i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
		i++;
	i--;
	while (i >= 0 && s[i] != c)
		i--;
	return (i);
}
