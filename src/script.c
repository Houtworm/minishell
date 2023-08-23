/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   script.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/23 14:59:51 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/23 04:37:04 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (i < argc)
	{
		fd = open(argv[1], O_RDONLY);
		while (ret > 0)
		{
			ret = get_next_line(fd, &line); // write second GNL for \ at end of line
			ft_parseline(line, shell);
			ft_executecommands(shell);
			free(line);
		}
		i++;
	}
	// cleanup
	return (SUCCESS);
}
