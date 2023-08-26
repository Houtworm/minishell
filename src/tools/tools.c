/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tools.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/26 03:50:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 03:56:50 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long long	ft_gettimems(char **envp)
{
	char		*date;
	long long	currenttime;

	date = ft_system("date +%s%3N", envp);
	currenttime = ft_atol(date);
	free(date);
	return (currenttime);
}
