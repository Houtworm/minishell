/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test1.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 02:09:57 by houtworm     \___)=(___/                 */
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
	char	*str[2];

	str[0] = strdup("Hallo1");
	element[0] = ft_lstnew(str[0]);
	list = &element[0];
	r = 0;
	ft_lstclear(list, NULL);
	if (*list != NULL)
		r = 1;
	free(str[0]);
	return (r);
}
