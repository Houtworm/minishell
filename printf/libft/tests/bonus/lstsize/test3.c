/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test3.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 17:51:07 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	t_list	**list;
	t_list	*element[2];
	int		size;
	char	*str[2];

	str[0] = strdup("Hallo1");
	str[1] = strdup("Hallo2");
	element[0] = ft_lstnew(str[0]);
	element[1] = ft_lstnew(str[1]);
	list = &element[0];
	ft_lstadd_back(list, element[1]);
	size = ft_lstsize(element[1]);
	r = 0;
	if (size != 1)
		r = 1;
	free(str[0]);
	free(str[1]);
	free((*list)->next);
	free(*list);
	return (r);
}