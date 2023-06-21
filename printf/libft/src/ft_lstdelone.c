/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 19:06:46 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/07 00:40:31 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
	{
		free (lst);
		return ;
	}
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
