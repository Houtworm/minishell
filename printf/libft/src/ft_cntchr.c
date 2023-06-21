/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_cntchr.c                                        :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/06/11 17:23:36 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/07 00:38:41 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_cntchr(const char *str, char c, int s)
{
	int	i;
	int	t;

	i = 0;
	while (*str)
	{
		if (*str == c)
		{
			i++;
			str++;
		}
		t = s;
		while (t > 0)
		{
			str++;
			t--;
		}
	}
	return (i);
}
