/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   z.c                                             |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:10 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 02:33:17 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_z(t_cmds cmd)
{
	int		mshzfd;
	char	*line;
	char	*home;

	line = ft_gethome(cmd.envp);
	home = ft_strjoin(line, "/.mshz");
	mshzfd = open(home, O_RDONLY);
	free(line);
	while (get_next_line(mshzfd, &line) > 0)
	{
		if (ft_strnstr(line, cmd.arguments[1], ft_strlen(line)))
		{
			cmd.arguments[1] = ft_strdup(line);
			ft_chdir(cmd);
			free(line);
			return (0);
		}
		free(line);
	}
	close(mshzfd);
	return (1);
}
