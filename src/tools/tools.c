/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tools.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/26 03:50:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/28 09:44:23 by houtworm     \___)=(___/                 */
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

void	ft_printshell(t_shell shell)
{
	printf("%s\n", "shell struct");
	printf("forkamount: %d\n", shell.forkamount);
}

void	ft_printforks(t_forks forks)
{
	printf("%s\n", "forks struct");
	printf("pipeline: %s\n", forks.pipeline);
	printf("cmdamount: %d\n", forks.cmdamount);
}

void	ft_printcmds(t_cmds cmds)
{
	printf("%s\n", "cmds struct");
	printf("pipeline: %s\n", cmds.pipeline);
	printf("argument: %s\n", cmds.arguments[0]);
	printf("absolute: %s\n", cmds.absolute);
}
