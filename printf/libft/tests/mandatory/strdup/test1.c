/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:54:36 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 19:44:52 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*s;
	char	*r;

	ret = 0;
	s = "Hallo dit is een string";
	r = ft_strdup(s);
	if (strncmp(r, s, 23) != 0)
		ret = 1;
	free (r);
	return (ret);
}