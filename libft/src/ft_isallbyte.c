/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_isallbyte.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 01:43:42 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/03 04:50:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isallbyte(char *str, char byte)
{
	if (!str)
		return (1);
	while (*str == byte)
		str++;
	if (!*str)
		return (1);
	return (0);
}
