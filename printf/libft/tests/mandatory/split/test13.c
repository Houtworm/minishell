/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test13.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 22:05:18 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*str4;
	char	*s9;
	char	*s10;
	char	**r4;

	r = 0;
	str4 = "||split||th is||";
	s9 = "||split||th is||";
	r4 = ft_split(str4, 254);
	if (strncmp(r4[0], "||split||th is||", 16))
		r = 1;
	free(r4[0]);
	free(r4[1]);
	free(r4);
	return (r);
}
