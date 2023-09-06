/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:43 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/06 18:47:51 by djonker      \___)=(___/                 */
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

int	ft_mainloop(t_shell *shell)
{
	char	*line;
	int		forknumber;
	int		status;

	forknumber = 0;
	shell->envp = ft_fdtocharpp(shell->envpfd);
	ft_printprompt(shell, shell->envp);
	line = readline("❯ ");
	shell->starttime = ft_gettimems(shell->envp);
	if (!line)
		return (1);
	if (!ft_isallbyte(line, ' '))
	{
		add_history(line);
		*shell = ft_parseline(line, *shell);
		shell->code = ft_forktheforks(shell);
		while (shell->forkamount > forknumber)
		{
			waitpid(shell->forks[forknumber].pid, &status, 0);
			forknumber++;
		}
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-d\0", 3) == 0)
			shell =	ft_initstruct(envp, 1);
		else
			return (ft_runscript(argc, argv, envp));
	}
	else
		shell =	ft_initstruct(envp, 0);
	while (1)
		ft_mainloop(shell);
	return (0);
}
