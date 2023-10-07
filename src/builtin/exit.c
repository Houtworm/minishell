/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exit.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 18:48:08 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 02:30:28 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_cmds cmds, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmds.arguments[1])
		exit(0);
	if (cmds.arguments[1][i] == '-')
		i++;
	while (cmds.arguments[1][i])
	{
		if (cmds.arguments[1][i] < '0' || cmds.arguments[1][i] > '9' )
		{
			ft_putendl_fd("exit", 2);
			return (ft_moderrorreturn ("numeric argument required", "exit", cmds.arguments[1], 2));
		}
		i++;
	}
		return (ft_atol(cmds.arguments[1]));
	return (0);
	shell = shell;
}
