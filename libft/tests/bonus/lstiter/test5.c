/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test5.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 15:32:29 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

void	func(void *content)
{
	memset(content, 'a', 3);
}

int	main(void)
{
	int		r;
	t_list	*list;

	list = NULL;
	ft_lstiter(list, &func);
	r = 0;
	if (list)
		r = 1;
	return (r);
}
