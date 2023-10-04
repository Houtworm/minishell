/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   script.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/23 14:59:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/04 06:46:31 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_runscript(int argc, char **argv, t_shell *shell)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;
	int		code;

	i = 1;
	ret = 1;
	code = 0;
	/*shell->envp = ft_fdtocharpp(shell->envpfd);*/
	if (ft_strncmp(argv[1], "-c\0", 3) == 0)
	{
		ret = ft_parseline(argv[2], shell);
		if (ret == 1)
			return (0);
		if (ret == 2)
			return (2);
		if (ret == 127)
			if (ft_errorexit("command not found", "!!", 0))
				return (127);
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
