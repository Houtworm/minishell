/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   period.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:01:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:47:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkperiod(t_commands cmd)
{
	DIR		*dir;

	dir = opendir(cmd.arg[0]);
	if (dir || errno == EACCES)
	{
		closedir(dir);
		return (ft_errorret("Is a directory", cmd.arg[0], 126));
	}
	if (access(cmd.arg[0], F_OK))
		return (ft_errorret("No such file or directory", cmd.arg[0], 127));
	if ((access(cmd.arg[0], X_OK) || access(cmd.arg[0], R_OK)))
		return (ft_errorret("permission denied", cmd.arg[0], 126));
	return (0);
}

int	ft_period(t_commands cmd, t_shell *shell)
{
	int		status;
	int		fd;
	char	*line;

	if (cmd.arg[0][1] == '\0')
		return (ft_errorret("filename argument required", ".", 2));
	else if (cmd.arg[0][1] == '/' || cmd.arg[0][0] == '/')
	{
		status = ft_checkperiod(cmd);
		if (status)
			return (status);
		execve(cmd.absolute, cmd.arg, shell->envp);
		fd = open(cmd.absolute, O_RDONLY);
		if (fd == -1)
			return (ft_errorret("command not found", cmd.absolute, 127));
		status = 1;
		while (status > 0)
		{
			status = get_next_line(fd, &line);
			if (status <= 0)
			{
				free(line);
				close(fd);
				return (shell->code);
			}
			ft_freenewprompt(shell);
			if (ft_parseline(line, shell))
			{
				free(line);
				close(fd);
				return (2);
			}
			free(line);
			shell->code = ft_forktheforks(shell);
		}
		close(fd);
		return(shell->code);
	}
	else
		return (ft_errorret("command not found", cmd.arg[0], 127));
	return (0);
}
