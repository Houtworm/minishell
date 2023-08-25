/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:28 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/24 23:06:16 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*ft_initstruct(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(shell), 10);
	shell->envp = envp;
	shell->starttime = ft_gettimems(shell->envp);
	shell->code = 256;
	return (shell);
}
