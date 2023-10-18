/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 08:35:25 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:19:11 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	if (!s || n <= 0)
		return ;
	p = s;
	while (n)
	{
		*p = '\0';
		p++;
		n--;
	}
}
