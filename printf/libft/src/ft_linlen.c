/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_linlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 15:49:15 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:19:28 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_linlen(char *str)
{
	int		l;

	l = 0;
	while (*str != '\0' && *str != '\n')
	{
		l++;
		str++;
	}
	return (l);
}
