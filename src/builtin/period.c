/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   period.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:01:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 02:40:25 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkperiod(t_cmds cmds)
{
	DIR		*dir;

	dir = opendir(cmds.arguments[0]);
	if (dir || errno == EACCES)
	{
		closedir(dir);
		return (ft_errorreturn("Is a directory", cmds.arguments[0], 126));
	}
	if (access(cmds.arguments[0], F_OK))
		return (ft_errorreturn("No such file or directory", cmds.arguments[0], 127));
	if ((access(cmds.arguments[0], X_OK) || access(cmds.arguments[0], R_OK)))
		return (ft_errorreturn("permission denied", cmds.arguments[0], 126));
	return (0);
}

int	ft_period(t_cmds cmds, t_shell *shell)
{
	int		status;
	int		fd;
	char	*line;

	if (cmds.arguments[0][1] == '\0')
		return (ft_errorreturn("filename argument required", ".", 2));
	else if (cmds.arguments[0][1] == '/' || cmds.arguments[0][0] == '/')
	{
		status = ft_checkperiod(cmds);
		if (status)
			return (status);
		execve(cmds.absolute, cmds.arguments, shell->envp);
		fd = open(cmds.absolute, O_RDONLY);
		if (fd == -1)
			return (ft_errorreturn("command not found", cmds.absolute, 127));
		status = 1;
		while (status > 0)
		{
			status = get_next_line(fd, &line);
			if (status <= 0)
				exit (shell->code);
			if (ft_parseline(line, shell))
				exit (2);
			if (status > 0)
				shell->code = ft_forktheforks(shell);
			free(line);
		}
		return(shell->code);
	}
	else
		return (ft_errorreturn("command not found", cmds.arguments[0], 127));
	return (0);
}
