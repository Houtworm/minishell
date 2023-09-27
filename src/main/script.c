/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   script.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/23 14:59:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/27 09:33:48 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_runscript(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		fd;
	char	*line;
	int		ret;
	int		i;
	int		code;

	i = 1;
	ret = 1;
	code = 0;
	shell = ft_initstruct(envp, 0);
	shell->envp = ft_fdtocharpp(shell->envpfd);
	if (ft_strncmp(argv[1], "-c\0", 3) == 0)
	{
		if (ft_parseline(argv[2], shell))
		{
			return (2);
		}
			code = ft_forktheforks(shell);
	}
	else
	{
		while (i < argc)
		{
			fd = open(argv[1], O_RDONLY);
			while (ret > 0)
			{
				ret = get_next_line(fd, &line);
				if (ft_parseline(line, shell))
					return (2);
				code = ft_forktheforks(shell);
				free(line);
			}
			close(fd);
			i++;
		}
	}
	return (code);
}
