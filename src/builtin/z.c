/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   z.c                                             |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:10 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/05 19:33:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_z(t_cmds cmd, t_shell *shell)
{
	int		mshzfd;
	char	*line;
	char	*home;
	char	*temp;

	line = ft_gethome(shell->envp);
	home = ft_strjoin(line, "/.mshz");
	mshzfd = open(home, O_RDONLY);
	free(line);
	while (get_next_line(mshzfd, &line) > 0)
	{
		temp = ft_strrchr(line, '/');
		if (ft_strnstr(temp, cmd.arguments[1], ft_strlen(temp)))
		{
			cmd.arguments[1] = ft_strdup(line);
			ft_chdir(cmd, shell);
			free(line);
			free(home);
			/*free(temp);*/
			return (0);
		}
		/*free(temp);*/
		free(line);
	}
	close(mshzfd);
	mshzfd = open(home, O_RDONLY);
	while (get_next_line(mshzfd, &line) > 0)
	{
		if (ft_strnstr(line, cmd.arguments[1], ft_strlen(line)))
		{
			cmd.arguments[1] = ft_strdup(line);
			ft_chdir(cmd, shell);
			free(line);
			free(home);
			return (0);
		}
		free(line);
	}
	free(home);
	close(mshzfd);
	return (1);
}
