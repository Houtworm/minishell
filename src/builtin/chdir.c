/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   chdir.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 17:21:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/02 03:21:08 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_adddirtoz(t_cmds cmd, char *cwd)
{
	int		mshzfd;
	int		tempfd;
	char	*line;
	char	*home;

	line = ft_gethome(cmd.envp);
	home = ft_strjoin(line, "/.mshz");
	mshzfd = open(home, O_RDONLY);
	tempfd = open("/tmp/minishelltempz.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(line);
	ft_putendl_fd(cwd, tempfd);
	while (get_next_line(mshzfd, &line) > 0)
	{
		if (ft_strncmp(line, cwd, 500))
			ft_putendl_fd(line, tempfd);
		free(line);
	}
	close(tempfd);
	close(mshzfd);
	tempfd = open("/tmp/minishelltempz.tmp", O_RDONLY);
	mshzfd = open(home, O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(tempfd, &line) > 0)
	{
		ft_putendl_fd(line, mshzfd);
		free(line);
	}
	close(mshzfd);
	close(tempfd);
}

int	ft_chdir(t_cmds cmds)
{
	char	*line;
	char	*cwd;

	cwd = malloc(512);
	getcwd(cwd, 512);
	/*if (cmds.arguments[2]) // Edge case in split_not_quote? check the tester.. with these lines enabled*/
		/*if (ft_errorexit("too many arguments", "cd", 0))*/
			/*return (1);*/
	if (!ft_strncmp(cmds.arguments[1],  "~\0", 2) || !cmds.arguments[1])
		line = ft_gethome(cmds.envp);
	else if (!ft_strncmp(cmds.arguments[1],  "-\0", 2))
	{
		line = ft_getenvval(cmds.envp, "OLDPWD");
		printf("%s\n", line);
	}
	else
	{
		line = ft_strdup(cmds.arguments[1]);
	}
	if (chdir(line))
	{
		free(cwd);
		ft_moderrorexit("No such file or directory", cmds.arguments[0], cmds.arguments[1], 0);
		return (1);
	}
	free(line);
	ft_setenv(cmds.envp, "OLDPWD", cwd);
	getcwd(cwd, 512);
	ft_setenv(cmds.envp, "PWD", cwd);
	ft_adddirtoz(cmds, cwd);
	free(cwd);
	ft_charpptofd(cmds.envp, cmds.envpfd);
	return (0);
}
