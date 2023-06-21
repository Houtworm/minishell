/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test5.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 16:14:04 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

void	*func(void *content)
{
	memset(content, 'a', 3);
	return (content);
}

int	main(void)
{
	int		r;
	t_list	*list;
	t_list	*copy;

	list = NULL;
	copy = ft_lstmap(list, &func, &free);
	r = 0;
	if (copy)
		r = 1;
	return (r);
}
