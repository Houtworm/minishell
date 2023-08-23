/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:28 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/23 04:35:35 by djonker      \___)=(___/                 */
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
