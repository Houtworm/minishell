/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_gettimemsdate.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 20:10:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 16:59:08 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long	ft_gettimemsdate(char **envp)
{
	char		*date;
	long long	currenttime;

	date = ft_system("date +%s%3N", envp);
	currenttime = ft_atol(date);
	free(date);
	return (currenttime);
}
