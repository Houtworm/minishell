/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test20.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 22:31:27 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 10:42:00 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	char	*str;
	int		a;

	str = "c0ngr4tulat1ons";
	a = 0;
	if (ft_atoi(str) != a)
		return (1);
	return (0);
}
