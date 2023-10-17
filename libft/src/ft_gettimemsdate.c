/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_gettimemsdate.c                              |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/17 20:10:03 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 20:10:33 by houtworm     \___)=(___/                 */
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
