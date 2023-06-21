/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   returnpointer.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 22:40:17 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		r;
	int		f;

	alarm(5);
	s = strdup(argv[2]);
	r = printf(argv[1], s);
	f = ft_printf(argv[1], s);
	free(s);
	if (r != f)
		return (f);
	return (0);
}
