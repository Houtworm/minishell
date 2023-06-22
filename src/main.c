/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:49:35 by houtworm          #+#    #+#             */
/*   Updated: 2023/06/22 12:13:57 by houtworm         ###   ########.fr       */
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
		ft_executecommands(shell);
		ft_frearr(shell->arguments);
		free(shell->absolute);
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
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	if (argc > 1)
		return (ft_runscript(argc, argv, envp));
	while (TRUE)
		ft_mainloop(&shell, envp);
	return (SUCCESS);
}
