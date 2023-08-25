/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dupmachine.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 21:59:03 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 01:11:03 by houtworm     \___)=(___/                 */
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

/*int	ft_heredoc(char *delimiter)*/
/*{*/
	/*int		fdi;*/
	/*char	*line;*/
	/*int		length;*/

	/*fdi = open("/tmp/pipexfile.temp", O_RDWR | O_CREAT | O_TRUNC, 0666);*/
	/*length = ft_strlen(delimiter);*/
	/*ft_putstr("pipex heredoc> ");*/
	/*get_next_line(0, &line);*/
	/*if (!line)*/
		/*ft_errorexit("Error allocating memory", "malloc", 1);*/
	/*while (ft_strncmp(line, delimiter, length + 1))*/
	/*{*/
		/*ft_putstr("pipex heredoc> ");*/
		/*ft_putendl_fd(line, fdi);*/
		/*free(line);*/
		/*get_next_line(0, &line);*/
		/*if (!line)*/
			/*ft_errorexit("Error allocating memory", "malloc", 1);*/
	/*}*/
	/*free(line);*/
	/*close(fdi);*/
	/*fdi = open("/tmp/pipexfile.temp", O_RDONLY);*/
	/*dup2(fdi, 0);*/
	/*return (fdi);*/
/*}*/

/*int	ft_dupmachine(t_cmds cmds)*/
/*{*/
	/*int		heredoc;*/

	/*heredoc = 0;*/
	/*if (!ft_strncmp(argv[1], "here_doc", 9))*/
		/*heredoc = 1;*/
	/*if (heredoc && cmdnbr == 0)*/
		/*ft_heredoc(argv[2]);*/
	/*else if (cmdnbr == 0)*/
	/*{*/
		/*if (ft_inputfile(argv[1], argc, argv))*/
			/*return (1);*/
	/*}*/
	/*else*/
		/*dup2(pipes[cmdnbr][0], 0);*/
	/*if (cmdnbr == argc - 4 - heredoc)*/
	/*{*/
		/*if (ft_outputfile(heredoc, argc, argv))*/
			/*return (1);*/
	/*}*/
	/*else*/
		/*dup2(pipes[cmdnbr + 1][1], 1);*/
	/*return (0);*/
/*}*/
