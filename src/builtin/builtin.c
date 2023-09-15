/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   builtin.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 15:11:33 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/15 14:52:44 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_executebuiltin(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell, int ret)
{
	int	pid;
	int	code;

	pid = fork();
	if (pid == 0)
	{
		ft_dupmachine(cmds, cmdnbr, forknbr, shell);
		if (ret == 1)
			exit (ft_echo(cmds));
		else if (ret == 2)
			exit (ft_echo(cmds));
		else if (ret == 3)
			exit (ft_env());
		else if (ret == 4)
			exit (ft_export(cmds));
		else if (ret == 5)
			exit (ft_pwd(cmds));
		else if (ret == 6)
			exit (ft_unset(cmds));
	}
	waitpid(pid, &code, 0);
	code = WEXITSTATUS(code);
	shell->code = code;
	return (code);
}

struct	builtin
{
	char	*compare;
	int		(*func)(t_cmds cmds);
};

/*int	ft_builtinselector(t_shell shell, t_cmds cmds, int	(*func)(char *cmd, char *))*/
/*{*/
	
/*}*/

int	ft_builtincheck(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	ret;
	int i;
	struct builtin	bui[5] = {
	{"alias\0", ft_echo},
	{"echo\0", ft_echo},
	{"env\0", ft_echo},
	{"export\0", ft_echo},
	{"unset\0", ft_echo}
	};

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare) + 1))
			bui[i].func(cmds);
		i++;
	}
	ret = 0;
	/*if (!ft_strncmp(cmds.arguments[0], "alias\0", 6))*/
		/*ret = 1;*/
	/*else if (!ft_strncmp(cmds.arguments[0], "echo\0", 5))*/
		/*ret = 2;*/
	/*else if (!ft_strncmp(cmds.arguments[0], "env\0", 4))*/
		/*ret = 3;*/
	/*else if (!ft_strncmp(cmds.arguments[0], "export\0", 7))*/
		/*ret = 4;*/
	/*else if (!ft_strncmp(cmds.arguments[0], "pwd\0", 4))*/
		/*ret = 5;*/
	/*else if (!ft_strncmp(cmds.arguments[0], "unset\0", 6))*/
		/*ret = 6;*/
	if (!ft_strncmp(cmds.arguments[0], "exit\0", 5))
		ft_exit(cmds);
	else if (!ft_strncmp(cmds.arguments[0], "cd\0", 3))
		return (ft_chdir(cmds));
	else if (ret)
		return (ft_executebuiltin(cmds, cmdnbr, forknbr, shell, ret));
	return (-1111);
}
