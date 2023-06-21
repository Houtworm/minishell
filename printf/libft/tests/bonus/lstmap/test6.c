/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test6.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 21:06:17 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/04 17:54:49 by houtworm     \___)=(___/                 */
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
	t_list	*element[1];
	char	*str[1];

	str[0] = strdup("Hallo1");
	element[0] = ft_lstnew(str[0]);
	list = &element[0];
	copy = ft_lstmap(*list, &func, NULL);
	r = 0;
	if (strncmp(str[0], "aaalo1", 6))
		r = 1;
	free(str[0]);
	free(*list);
	free(copy);
	return (r);
}
