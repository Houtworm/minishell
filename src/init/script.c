/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   script.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/23 14:59:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 01:02:54 by houtworm     \___)=(___/                 */
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

	i = 1;
	ret = 1;
	shell = ft_initstruct(envp);
	if (ft_strncmp(argv[1], "-c", 1) == 0)
	{
		ft_parseline(argv[2], shell);
		ft_forktheforks(shell);
	}
	else
	{
		while (i < argc)
		{
			fd = open(argv[1], O_RDONLY);
			while (ret > 0)
			{
				ret = get_next_line(fd, &line); // write second GNL for \ at end of line
				ft_parseline(line, shell);
				ft_forktheforks(shell);
				free(line);
			}
			i++;
		}
	}
	// cleanup
	return (SUCCESS);
}