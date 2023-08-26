/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   chdir.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 17:21:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 11:49:41 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_chdir(t_cmds cmds)
{
	char	*line;
	int		i;
	char	*cwd;

	cwd = malloc(512);
	getcwd(cwd, 512);
	i = 0;
	if (!ft_strncmp(cmds.arguments[1],  "~\0", 2) || !cmds.arguments[1])
		line = ft_gethome(*cmds.envp);
	else if (!ft_strncmp(cmds.arguments[1],  "-\0", 2))
		line = ft_getenvval(*cmds.envp, "OLDPWD");
	else
	{
		line = cmds.arguments[1];
	}
	if (chdir(line))
	{
		free(cwd);
		ft_moderrorexit("No such file or directory", cmds.arguments[0], cmds.arguments[1], 1);
	}
	ft_setenv(*cmds.envp, "OLDPWD", cwd);
	getcwd(cwd, 512);
	ft_setenv(*cmds.envp, "PWD", cwd);
	ft_printf("%s\n", ft_getenvval(*cmds.envp, "PWD"));
	free(cwd);
	ft_charpptofd(*cmds.envp, cmds.envpfd);
	return (0);
}
