/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   builtin.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 15:11:33 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 02:45:26 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_setbuiltincompare(t_builtin *builtins)
{
	builtins[0].compare = ft_strdup(".\0");
	builtins[1].compare = ft_strdup("/\0");
	builtins[2].compare = ft_strdup("alias\0");
	builtins[3].compare = ft_strdup("echo\0");
	builtins[4].compare = ft_strdup("env\0");
	builtins[5].compare = ft_strdup("export\0");
	builtins[6].compare = ft_strdup("unset\0");
	builtins[7].compare = ft_strdup("pwd\0");
	builtins[8].compare = ft_strdup("which\0");
	builtins[9].compare = ft_strdup("cd\0");
	builtins[10].compare = ft_strdup("z\0");
	builtins[11].compare = ft_strdup("exit\0");
	builtins[12].compare = ft_strdup("exec\0");
	builtins[13].compare = NULL;
}

t_builtin	*ft_getbuiltins(void)
{
	t_builtin	*builtins;

	builtins = ft_calloc(14, 16);
	builtins[0].func = ft_period;
	builtins[1].func = ft_period;
	builtins[2].func = ft_alias;
	builtins[3].func = ft_echo;
	builtins[4].func = ft_env;
	builtins[5].func = ft_export;
	builtins[6].func = ft_unset;
	builtins[7].func = ft_pwd;
	builtins[8].func = ft_which;
	builtins[9].func = ft_chdir;
	builtins[10].func = ft_z;
	builtins[11].func = ft_exit;
	builtins[12].func = ft_exec;
	ft_setbuiltincompare(builtins);
	return (builtins);
}

int	ft_builtinexecute(int cmdnbr, int forknbr, t_shell *shell, int i)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == 0)
	{
		ft_dupmachine(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr, shell);
		exit(shell->builtins[i].func(shell->forks[forknbr].cmds[cmdnbr], shell));
	}
	waitpid(pid, &ret, 0);
	shell->code = WEXITSTATUS(ret);
	if (i > 10)
		ft_freeexit(shell, shell->code);
	return (shell->code);
}

int	ft_builtincheck(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		if (!ft_strncmp(cmds.arguments[0], shell->builtins[i].compare, ft_strlen(shell->builtins[i].compare) + j))
			return (ft_builtinexecute(cmdnbr, forknbr, shell, i));
		if (i == 1)
			j = 1;
		i++;
	}
	return (-1111);
}
