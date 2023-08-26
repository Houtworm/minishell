/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   chdir.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 17:21:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 03:55:34 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	ft_chdir(t_cmds cmds)*/
/*{*/
	/*char	*line;*/
	/*char	*dir;*/
	/*int		i;*/
	/*char	*cwd;*/

	/*cwd = malloc(512);*/
	/*getcwd(cwd, 512);*/
	/*i = 0;*/
	/*dir = ft_calloc(512, 1);*/
	/*line = shell->line;*/
	/*while (line[i + 2] != '\0')*/
	/*{*/
		/*while (line[i + 3] == ' ')*/
			/*i++;*/
		/*dir[i] = line[i + 3];*/
		/*i++;*/
	/*}*/
	/*if (!ft_strncmp(dir,  "~\0", 2) || i == 0)*/
	/*{*/
		/*dir = ft_gethome(shell->envp);*/
	/*}*/
	/*if (!ft_strncmp(dir,  "-\0", 2))*/
	/*{*/
		/*dir = ft_getenvval(shell->envp, "OLDPWD");*/
	/*}*/
	/*if (chdir(dir))*/
	/*{*/
		/*free(dir);*/
		/*free(cwd);*/
		/*return (1);*/
	/*}*/
	/*ft_setenv(shell->envp, "OLDPWD", cwd);*/
	/*getcwd(cwd, 512);*/
	/*ft_setenv(shell->envp, "PWD", cwd);*/
	/*free(dir);*/
	/*free(cwd);*/
	/*return (0);*/
/*}*/
