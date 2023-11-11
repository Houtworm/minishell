/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:43 by djonker       #+#    #+#                 */
/*   Updated: 2023/11/11 07:57:05 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_retcode;

int	ft_mainloop(t_shell *msh)
{
	char	*line;

	ft_printprompt(msh, msh->envp);
	line = readline("$ ");
	if (!line)
		ft_freeexit(msh, 0);
	msh->starttime = ft_gettimemsdate(msh->envp, msh->sysfile);
	if (!ft_isallbyte(line, ' '))
	{
		ft_writehistory(line, msh->historyfile, msh);
		g_retcode = ft_parseline(line, msh, 0);
		if (g_retcode)
			return (g_retcode);
		g_retcode = ft_forktheforks(msh);
		ft_freenewprompt(msh);
		free(line);
	}
	return (0);
}

int	ft_runscript(char *file, t_shell *msh)
{
	int		fd;
	char	*line;
	int		ret;
	int		code;

	ret = 1;
	code = ft_strlen(file);
	if (file[code - 1] != 'h' || file[code - 2] != 's' || file[code - 3] != '.')
		return (ft_errorret("Can only execute scripts", "argument", 1));
	fd = open(file, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_parseline(line, msh, 0))
		{
			close(fd);
			free(line);
			return (2);
		}
		code = ft_forktheforks(msh);
		ft_freenewprompt(msh);
		free(line);
	}
	close(fd);
	return (code);
}

int	ft_singlecommand(t_shell *msh, char *line)
{
	int		ret;

	ret = ft_parseline(line, msh, 0);
	if (ret)
	{
		if (ret == 4)
			return (0);
		else
			return (ret);
	}
	return (ft_forktheforks(msh));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*msh;

	rl_event_hook = ft_sighook;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-d\0", 3) == 0)
			msh = ft_initstruct(envp, 1);
		else
		{
			msh = ft_initstruct(envp, 0);
			if (ft_strncmp(argv[1], "-c\0", 3) == 0)
				ft_freeexit(msh, ft_singlecommand(msh, argv[2]));
			else
				ft_freeexit(msh, ft_runscript(argv[1], msh));
		}
	}
	else
		msh = ft_initstruct(envp, 0);
	while (1)
		ft_mainloop(msh);
	ft_freeexit(msh, 0);
}
