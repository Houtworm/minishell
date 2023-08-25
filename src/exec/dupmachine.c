/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dupmachine.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 21:59:03 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 04:54:14 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_errorexit(char *reason, char *cmd, int code)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
	if (code)
		exit (code);
	else
		return (1);
}

/*int	ft_checkfiles(int argc, char **argv, int file)*/
/*{*/
	/*if (!file)*/
	/*{*/
		/*if (ft_strncmp(argv[1], "here_doc", 9))*/
		/*{*/
			/*if (access(argv[1], R_OK) < 0)*/
			/*{*/
				/*if (access(argv[1], F_OK) < 0)*/
					/*ft_errorexit("no such file or directory", argv[1], 0);*/
				/*else*/
					/*ft_errorexit("permission denied", argv[1], 0);*/
				/*return (1);*/
			/*}*/
		/*}*/
	/*}*/
	/*else*/
	/*{*/
		/*if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))*/
		/*{*/
			/*ft_errorexit("permission denied", argv[argc - 1], 0);*/
			/*return (1);*/
		/*}*/
	/*}*/
	/*return (0);*/
/*}*/

/*int	ft_checkcommands(char **current, char **paths, char **cmd, int cmdnbr)*/
/*{*/
	/*int		i;*/
	/*char	*temp;*/

	/*i = 0;*/
	/*if (current[0] && ft_chrstr('/', current[0]))*/
		/*temp = ft_strjoin(NULL, current[0]);*/
	/*else*/
		/*temp = ft_strjoin(paths[i], current[0]);*/
	/*while (access(temp, F_OK) && paths[i] && !ft_chrstr('/', current[0]))*/
	/*{*/
		/*free(temp);*/
		/*i++;*/
		/*temp = ft_strjoin(paths[i], current[0]);*/
	/*}*/
	/*if (!paths[i] || ft_isallbyte(cmd[cmdnbr], ' ') || access(temp, F_OK))*/
		/*if (ft_errorexit("command not found", cmd[cmdnbr], 0))*/
			/*i = 127;*/
	/*if (access(temp, X_OK) && i != 127)*/
		/*if (ft_errorexit("permission denied", current[0], 0))*/
			/*i = 126;*/
	/*free (temp);*/
	/*return (i);*/
/*}*/

int	ft_heredoc(char *delimiter)
{
	int		fdi;
	char	*line;
	int		length;

	fdi = open("/tmp/minishellheredocfile.temp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(delimiter);
	ft_putstr("minishell heredoc> ");
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, delimiter, length + 1))
	{
		ft_putstr("minishell heredoc> ");
		ft_putendl_fd(line, fdi);
		free(line);
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
	}
	free(line);
	close(fdi);
	fdi = open("/tmp/minishellheredocfile.temp", O_RDONLY);
	dup2(fdi, 0);
	return (fdi);
}

int	ft_dupmachine(t_cmds cmds)
{
	// check if cmdnbr == 0 and forknbr > 0 then fd_in is output from pipe
	if (cmds.redirect[0].fd_in == -1)
		cmds.redirect[0].fd_in = ft_heredoc(cmds.redirect[0].heredocdelimiter);
	else
		dup2(cmds.redirect[0].fd_in, 0);
	// check if cmdnumber == cmdamount and forknumber < forkamount. then fd_out is dupped to pipe.
	dup2(cmds.redirect[0].fd_out, 1);
	return (0);
}
