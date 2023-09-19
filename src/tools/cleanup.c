/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   cleanup.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 01:18:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 01:19:07 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleanexit(t_shell *shell)
{
	free(shell);
	exit (0);
}
