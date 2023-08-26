/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   main.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:43 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 07:41:12 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	int		forknumber;
	int		status;

	forknumber = 0;
	shell->envp = ft_fdtocharpp(shell->envpfd); //segfaults
	ft_printprompt(shell, envp);
	line = readline("❯ ");
	shell->starttime = ft_gettimems(shell->envp);
	if (!line)
		return (1);
	if (!ft_isallbyte(line, ' '))
	{
		add_history(line);
		ft_parseline(line, shell);
		shell->code = ft_forktheforks(shell);
		while (shell->forkamount > forknumber)
		{
			waitpid(shell->forks[forknumber].pid, &status, 0);
			forknumber++;
		}
		ft_frearr(shell->forks[0].cmds[0].arguments);
		free(shell->forks[0].cmds[0].absolute);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell =	ft_initstruct(envp);
	/*signal(SIGINT, ft_sighandler);*/ //leave commented out untill builtins are fixed
	signal(SIGQUIT, ft_sighandler);
	if (argc > 1)
		return (ft_runscript(argc, argv, envp));
	while (1)
		ft_mainloop(shell, envp);
	return (0);
}
