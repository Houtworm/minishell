/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test1.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/23 13:57:30 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	t_list	*list;

	r = 0;
	list = ft_lstnew("Hallo");
	if (strncmp(list->content, "Hallo", 5))
		r = 1;
	free (list);
	return (r);
}