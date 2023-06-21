/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 08:45:34 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:51 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		a++;
		str++;
	}
	return (a);
}
