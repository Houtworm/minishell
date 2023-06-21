/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 17:19:46 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:03 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isxdigit(char *str)
{
	while (*str != '\0')
	{
		if ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))
			str++;
		else if (*str >= '0' && *str <= '9')
			str++;
		else
			return (0);
	}
	return (1);
}
