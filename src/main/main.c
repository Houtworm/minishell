/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:43 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/01 02:07:13 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mainloop(t_shell *shell)
{
	char	*line;
	int		ret;

	shell->stop = 0;
	shell->envp = ft_fdtocharpp(shell->envpfd);
	ft_printprompt(shell, shell->envp);
	line = readline("❯ ");
	if (!line)
		ft_cleanexit(shell);
	shell->starttime = ft_gettimems(shell->envp);
	if (!ft_isallbyte(line, ' '))
	{
		ft_addhistory(line, shell->historyfile);
		ret = ft_parseline(line, shell);
		if (ret == 2)
		{
			free(line);
			shell->code = 2;
			return (2);
		}
		if (ret == 127)
		{
			ft_errorexit("command not found", "!!", 0);
			return (127);
		}
		if (ret == 1)
			return (1);
		shell->code = ft_forktheforks(shell);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	rl_event_hook = ft_sighook;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
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
