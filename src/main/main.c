/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:43 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/07 03:32:29 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_mainloop(t_shell *shell)
{
	char	*line;
	int		ret;

	shell->stop = 0;
	ft_printprompt(shell, shell->envp);
	line = readline("$ "); // ❯ causes issues :(
	if (!line)
		ft_freeexit(shell, 0);
	shell->starttime = ft_gettimems(shell->envp);
	if (!ft_isallbyte(line, ' '))
	{
		ft_writehistory(line, shell->historyfile);
		ret = ft_parseline(line, shell);
		if (ret == 2)
		{
			shell->code = 2;
			return (2);
		}
		if (ret == 127)
			return (ft_errorreturn("command not found", "!!", 127));
		if (ret == 1)
			return (1);
		shell->code = ft_forktheforks(shell);
		ft_freenewprompt(shell);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		code;

	rl_event_hook = ft_sighook;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-d\0", 3) == 0)
			shell =	ft_initstruct(envp, 1);
		else
		{
			shell = ft_initstruct(envp, 0);
			code = ft_runscript(argc, argv, shell);
			ft_freeexit(shell, code);
		}
	}
	else
		shell =	ft_initstruct(envp, 0);
	while (1)
		ft_mainloop(shell);
	ft_freeexit(shell, 0);
}
