/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   main.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:43 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 02:08:25 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		// stop it from printing ^C on the prompt
		//somehow break the mainloop
	}
	if (sig == SIGQUIT)
	{
		// stop it from printing ^\ on the prompt
		// quit the current child
	}
}

int	ft_mainloop(t_shell *shell, char **envp)
{
	char	*line;

	ft_printprompt(shell, envp);
	line = readline(SHELL_PROMPT);
	shell->starttime = ft_gettimems(shell->envp);
	if (!line)
		return (ERROR);
	if (!ft_isallbyte(line, ' '))
	{
		add_history(line);
		ft_parseline(line, shell);
		ft_forktheforks(shell);
		ft_frearr(shell->forks[0].cmds[0].arguments);
		free(shell->forks[0].cmds[0].absolute);
		free(line);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.envp = envp;
	shell.starttime = ft_gettimems(shell.envp);
	shell.code = 256;
	/*signal(SIGINT, ft_sighandler);*/
	signal(SIGQUIT, ft_sighandler);
	if (argc > 1)
		return (ft_runscript(argc, argv, envp));
	while (TRUE)
		ft_mainloop(&shell, envp);
	return (SUCCESS);
}
