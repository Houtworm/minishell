/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test5.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/03 17:51:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	t_list	**list;
	t_list	*last;

	list = NULL;
	last = ft_lstlast(*list);
	r = 0;
	if (last)
		r = 1;
	return (r);
}
