/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test13.c                                           :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:06:47 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/24 13:00:51 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = '\t';
	if (ft_isdigit(c))
		return (1);
	return (0);
}
