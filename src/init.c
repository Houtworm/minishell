/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:21:10 by houtworm          #+#    #+#             */
/*   Updated: 2023/05/24 04:35:47 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*ft_initstruct(char **envp)
{
	t_shell	*strct;

	strct = ft_calloc(sizeof(strct), 10);
	strct->envp = envp;
	strct->starttime = ft_gettimems(strct->envp);
	strct->code = 256;
	return (strct);
}
