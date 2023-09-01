/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:28 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/01 06:27:56 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*ft_initstruct(char **envp)
{
	t_shell	*shell;
	int		shlvlint;
	char	*shlvlstr;

	shell = ft_calloc(sizeof(shell), 10);
	shell->envp = envp;
	shlvlint = ft_atoi(ft_getenvval(shell->envp, "SHLVL"));
	shlvlint++;
	shlvlstr = ft_itoa(shlvlint);
	ft_setenv(shell->envp, "SHLVL", shlvlstr);
	/*ft_setenv(shell->envp, "?", "0"); // segfaults*/
	shell->envpfd = open("/tmp/minishellenvpfile.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_charpptofd(envp, shell->envpfd);
	shell->starttime = ft_gettimems(shell->envp);
	shell->code = 256;
	close(shell->envpfd);
	return (shell);
}
