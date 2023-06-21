/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vastrjoin.c                                  |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 16:17:34 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/20 13:46:04 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

char	*ft_vastrjoin(int n, ...)
{
	char	*temp1;
	char	*temp2;
	int		i;
	va_list	va;

	va_start(va, n);
	temp1 = ft_strdup(va_arg(va, char *));
	i = 1;
	while (i < n)
	{
		temp2 = ft_strjoin(temp1, va_arg(va, char *));
		free(temp1);
		temp1 = ft_strdup(temp2);
		free(temp2);
		i++;
	}
	va_end(va);
	return (temp1);
}
