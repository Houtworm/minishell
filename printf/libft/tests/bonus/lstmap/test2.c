/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test2.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 17:54:21 by houtworm     \___)=(___/                 */
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
	t_list	**list;
	t_list	*copy;
	t_list	*element[2];
	char	*str[2];

	str[0] = strdup("Hallo1");
	str[1] = strdup("Hallo2");
	element[0] = ft_lstnew(str[0]);
	element[1] = ft_lstnew(str[1]);
	list = &element[0];
	ft_lstadd_back(list, element[1]);
	copy = ft_lstmap(*list, &func, &free);
	r = 0;
	if (strncmp(str[0], "aaalo1", 6) || strncmp(str[1], "aaalo2", 6))
		r = 1;
	free(str[0]);
	free(str[1]);
	free((*list)->next);
	free(*list);
	free(copy->next);
	free(copy);
	return (r);
}
