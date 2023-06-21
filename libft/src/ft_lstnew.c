/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 04:38:37 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:35 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*r;

	r = malloc(sizeof(t_list));
	if (r == NULL)
		return (NULL);
	r->content = content;
	r->next = NULL;
	return (r);
}
