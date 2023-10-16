/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   z.c                                             |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:10 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 09:18:19 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_zgetfile(t_shell *shell)
{
	char	*home;
	char	*ret;

	home = ft_gethome(shell->envp);
	ret = ft_strjoin(home, "/.mshz");
	free(home);
	return (ret);
}

int	ft_zprint(char *file)
{
	int		mshzfd;
	char	*line;

	mshzfd = open(file, O_RDONLY);
	while (get_next_line(mshzfd, &line) > 0)
	{
		ft_putendl(line);
		free(line);
	}
	free(file);
	free(line);
	close(mshzfd);
	return (0);
}

int	ft_ztrydir(t_cmds cmd, t_shell *shell, char *file)
{
	int		mshzfd;
	char	*line;
	char	*temp;

	mshzfd = open(file, O_RDONLY);
	while (get_next_line(mshzfd, &line) > 0)
	{
		temp = ft_strrchr(line, '/');
		if (ft_strnstr(temp, cmd.arguments[1], ft_strlen(temp)))
		{
			free(cmd.arguments[1]);
			cmd.arguments[1] = ft_strdup(line);
			free(file);
			free(line);
			close(mshzfd);
			ft_chdir(cmd, shell);
			return (1);
		}
		free(line);
	}
	free(line);
	close(mshzfd);
	return (0);
}

int	ft_ztrypath(t_cmds cmd, t_shell *shell, char *file)
{
	int		mshzfd;
	char	*line;

	mshzfd = open(file, O_RDONLY);
	while (get_next_line(mshzfd, &line) > 0)
	{
		if (ft_strnstr(line, cmd.arguments[1], ft_strlen(line)))
		{
			free(cmd.arguments[1]);
			cmd.arguments[1] = ft_strdup(line);
			free(line);
			free(file);
			close(mshzfd);
			ft_chdir(cmd, shell);
			return (1);
		}
		free(line);
	}
	free(line);
	close(mshzfd);
	return (0);
}

int	ft_z(t_cmds cmd, t_shell *shell)
{
	char	*file;

	file = ft_zgetfile(shell);
	if (!cmd.arguments[1])
		return (ft_zprint(file));
	if (ft_ztrydir(cmd, shell, file))
		return (0);
	if (ft_ztrypath(cmd, shell, file))
		return (0);
	free(file);
	return (1);
}
