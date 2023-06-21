/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:20:32 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/25 16:18:01 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;
	char	*t;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	p = malloc(count * size);
	if (p == NULL)
		return (0x0);
	if (p)
	{
		t = p;
		i = 0;
		while (count * size > i)
		{
			t[i] = '\0';
			i++;
		}
	}
	return (p);
}
