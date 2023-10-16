/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 15:11:33 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 10:58:54 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_setbuiltincompare(t_builtin *builtins)
{
	builtins[0].compare = ft_strdup(".\0");
	builtins[1].compare = ft_strdup("/\0");
	builtins[2].compare = ft_strdup("echo\0");
	builtins[3].compare = ft_strdup("env\0");
	builtins[4].compare = ft_strdup("export\0");
	builtins[5].compare = ft_strdup("unset\0");
	builtins[6].compare = ft_strdup("pwd\0");
	builtins[7].compare = ft_strdup("which\0");
	builtins[8].compare = ft_strdup("exit\0");
	builtins[9].compare = ft_strdup("exec\0");
	builtins[10].compare = ft_strdup("alias\0");
	builtins[11].compare = ft_strdup("cd\0");
	builtins[12].compare = ft_strdup("z\0");
	builtins[13].compare = NULL;
}

t_builtin	*ft_getbuiltins(void)
{
	t_builtin	*builtins;

	builtins = ft_calloc(14, 16);
	builtins[0].func = ft_period;
	builtins[1].func = ft_period;
	builtins[2].func = ft_echo;
	builtins[3].func = ft_env;
	builtins[4].func = ft_export;
	builtins[5].func = ft_unset;
	builtins[6].func = ft_pwd;
	builtins[7].func = ft_which;
	builtins[8].func = ft_exit;
	builtins[9].func = ft_exec;
	builtins[10].func = ft_alias;
	builtins[11].func = ft_chdir;
	builtins[12].func = ft_z;
	ft_setbuiltincompare(builtins);
	return (builtins);
}

int	ft_builtinexecute(int cmdnbr, int forknbr, t_shell *msh, int i)
{
	int		pid;
	int		ret;
	char	*itoa;
	char	*outtmp;
	int		hdn;

	hdn = 0;
	if (i < 10)
	{
		if (msh->frk[forknbr].cmd[cmdnbr].heredoc)
		{
			while (hdn + 1 < msh->frk[forknbr].cmd[cmdnbr].heredoc)
			{
				pid = fork();
				if (pid == 0)
				{
					if (ft_dupmachine(cmdnbr, forknbr, hdn, msh) == 2)
						exit (1);
					if (msh->forkamount > 1)
					{
						close(msh->pipes[forknbr][1]);
						close(msh->pipes[forknbr][0]);
						close(msh->pipes[forknbr + 1][1]);
						close(msh->pipes[forknbr + 1][0]);
					}
					exit(msh->builtins[i].func(msh->frk[forknbr].cmd[cmdnbr], msh));
				}
				waitpid(pid, &ret, 0);
				msh->code = WEXITSTATUS(ret);
				if (i == 8 || i == 9)
					ft_freeexit(msh, msh->code);
				hdn++;
			}
		}
		pid = fork();
		if (pid == 0)
		{
			if (ft_dupmachine(cmdnbr, forknbr, hdn, msh) == 2)
				exit (1);
			if (msh->forkamount > 1)
			{
				close(msh->pipes[forknbr][1]);
				close(msh->pipes[forknbr][0]);
				close(msh->pipes[forknbr + 1][1]);
				close(msh->pipes[forknbr + 1][0]);
			}
			exit(msh->builtins[i].func(msh->frk[forknbr].cmd[cmdnbr], msh));
		}
		waitpid(pid, &ret, 0);
		msh->code = WEXITSTATUS(ret);
		if (i == 8 || i == 9)
			ft_freeexit(msh, msh->code);
	}
	else
	{
		itoa = ft_itoa(forknbr);
		outtmp = ft_vastrjoin(3, "/tmp/minishell/outputfile", itoa, ".tmp");
		pid = open(outtmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
		free(itoa);
		free(outtmp);
		close(pid);
		msh-> code = msh->builtins[i].func(msh->frk[forknbr].cmd[cmdnbr], msh);
	}
	return (msh->code);
}

int	ft_builtincheck(t_commands cmd, int cmdnbr, int forknbr, t_shell *msh)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		if (!ft_strncmp(cmd.arg[0], msh->builtins[i].compare, ft_strlen(msh->builtins[i].compare) + j))
			return (ft_builtinexecute(cmdnbr, forknbr, msh, i));
		if (i == 1)
			j = 1;
		i++;
	}
	return (-1111);
}
