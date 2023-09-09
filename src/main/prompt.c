/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   prompt.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/22 13:26:25 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 03:52:21 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_addosuserandhosttoprompt(char **envp)
{
	char	*prompt;
	char	*tmp;
	char	*osuser;
	char	*hostname;

	osuser = ft_system("uname -s", envp);
	tmp = ft_vastrjoin(3, "\n\e[30;46m ", osuser, " \e[36;45m\e[30m ");
	free(osuser);
	osuser = ft_system("hostname", envp);
	prompt = ft_strchr(osuser, '.');
	hostname = ft_substr(osuser, 0, ft_strlen(osuser) - ft_strlen(prompt));
	free(osuser);
	osuser = ft_getuser(envp);
	prompt = ft_vastrjoin(5, tmp, osuser, "@", hostname, " \e[35;43m\e[0m");
	ft_vafree(3, tmp, osuser, hostname);
	return (prompt);
}

char	*ft_addworkingdirectory(char *prompt, char **envp)
{
	char	*dir;
	char	*tmp;
	char	*user;

	dir = ft_getpwd(envp, 0);
	tmp = ft_gethome(envp);
	if (!ft_strncmp(tmp, dir, ft_strlen(tmp) - 1))
	{
		user = ft_substr(dir, ft_strlen(tmp) + 1, ft_strlen(dir));
		free(dir);
		dir = ft_strjoin("~/", user);
		free(user);
	}
	free(tmp);
	tmp = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(ft_strrchr(dir, '/')));
	user = ft_substr(ft_strrchr(dir, '/'), 1, ft_strlen(dir));
	free(dir);
	dir = ft_vastrjoin(3, prompt, "\e[30;43m ", tmp);
	ft_vafree(2, tmp, prompt);
	prompt = ft_vastrjoin(4, dir, "/\e[1m", user, " \e[0;33;44m");
	ft_vafree(2, dir, user);
	return (prompt);
}

char	*ft_addexecutiontime(t_shell *shell, char *temp, char **envp)
{
	char				*date;
	char				*prompt;
	long long			diff;

	diff = ft_gettimems(envp) - shell->starttime;
	date = ft_ltoa(diff);
	prompt = ft_vastrjoin(3, temp, "\e[0;30;44m ", date);
	ft_vafree(2, date, temp);
	return (prompt);
}

char	*ft_addreturncode(t_shell *shell, char *temp)
{
	char	*prompt;
	char	*temp2;

	if (shell->code != 256)
	{
		if (shell->code)
			temp2 = ft_strjoin(temp, "ms \e[34;41m\e[30;41m ");
		else
			temp2 = ft_strjoin(temp, "ms \e[34;42m\e[30;42m ");
		free(temp);
		temp = ft_itoa(shell->code);
		if (shell->code)
			prompt = ft_vastrjoin(3, temp2, temp, " ✘ \e[31;49m\e[0;0m\n");
		else
			prompt = ft_strjoin(temp2, "✔ \e[32;49m\e[0;0m\n");
		free(temp2);
	}
	else
		prompt = ft_strjoin(temp, "ms \e[34;49m\e[0;0m\n");
	free(temp);
	return (prompt);
}

void	ft_printprompt(t_shell *shell, char **envp)
{
	char	*prompt;

	prompt = ft_addosuserandhosttoprompt(envp);
	prompt = ft_addworkingdirectory(prompt, envp);
	prompt = ft_addexecutiontime(shell, prompt, envp);
	prompt = ft_addreturncode(shell, prompt);
	ft_printf(prompt);
	free(prompt);
}
