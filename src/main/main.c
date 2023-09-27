/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:43 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/27 07:52:07 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mainloop(t_shell *shell)
{
	char	*line;

	shell->stop = 0;
	shell->envp = ft_fdtocharpp(shell->envpfd);
	ft_printprompt(shell, shell->envp);
	line = readline("❯ ");
	if (!line)
		ft_cleanexit(shell);
	shell->starttime = ft_gettimems(shell->envp);
	if (!line)
		return (1);
	if (!ft_isallbyte(line, ' '))
	{
		add_history(line);
		if (ft_parseline(line, shell))
		{
			free(line);
			return (0);
		}
		shell->code = ft_forktheforks(shell);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	signal(SIGTSTP, ft_sighandler);
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
