/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 15:11:33 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/25 04:31:57 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_setbuiltincommand(t_builtin *bltn)
{
	bltn[0].cmnd = ft_strdup(".\0");
	bltn[1].cmnd = ft_strdup("/\0");
	bltn[2].cmnd = ft_strdup("echo\0");
	bltn[3].cmnd = ft_strdup("env\0");
	bltn[4].cmnd = ft_strdup("export\0");
	bltn[5].cmnd = ft_strdup("unset\0");
	bltn[6].cmnd = ft_strdup("pwd\0");
	bltn[7].cmnd = ft_strdup("which\0");
	bltn[8].cmnd = ft_strdup("exit\0");
	bltn[9].cmnd = ft_strdup("exec\0");
	bltn[10].cmnd = ft_strdup("alias\0");
	bltn[11].cmnd = ft_strdup("cd\0");
	bltn[12].cmnd = ft_strdup("z\0");
	bltn[13].cmnd = NULL;
}

t_builtin	*ft_getbuiltins(void)
{
	t_builtin	*bltn;

	bltn = ft_calloc(14, 16);
	bltn[0].func = ft_period;
	bltn[1].func = ft_period;
	bltn[2].func = ft_echo;
	bltn[3].func = ft_env;
	bltn[4].func = ft_export;
	bltn[5].func = ft_unset;
	bltn[6].func = ft_pwd;
	bltn[7].func = ft_which;
	bltn[8].func = ft_exit;
	bltn[9].func = ft_exec;
	bltn[10].func = ft_alias;
	bltn[11].func = ft_chdir;
	bltn[12].func = ft_z;
	ft_setbuiltincommand(bltn);
	return (bltn);
}

void	ft_builtinfork(int cmdnbr, int forknbr, t_shell *msh, int i)
{
	int		pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		if (ft_dupmachine(cmdnbr, forknbr, msh) == 2)
			exit (1);
		if (msh->forks > 1)
		{
			close(msh->pipes[forknbr][1]);
			close(msh->pipes[forknbr][0]);
			close(msh->pipes[forknbr + 1][1]);
			close(msh->pipes[forknbr + 1][0]);
		}
		exit(msh->bltn[i].func(msh->frk[forknbr].cmd[cmdnbr], msh));
	}
	waitpid(pid, &ret, 0);
	msh->code = WEXITSTATUS(ret);
	if (i == 8 || i == 9)
		ft_freeexit(msh, msh->code);
}

int	ft_builtinexecute(int cmdnbr, int forknbr, t_shell *msh, int i)
{
	char	*itoa;
	char	*outtmp;
	int		fd;

	if (i < 10)
		ft_builtinfork(cmdnbr, forknbr, msh, i);
	else
	{
		itoa = ft_itoa(forknbr);
		outtmp = ft_vastrjoin(4, msh->tmpdir, "outputfile", itoa, ".tmp");
		fd = open(outtmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
		free(itoa);
		free(outtmp);
		close(fd);
		msh->code = msh->bltn[i].func(msh->frk[forknbr].cmd[cmdnbr], msh);
	}
	return (msh->code);
}

int	ft_builtincheck(t_commands cmd, int cmdnbr, int forknbr, t_shell *msh)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < 13)
	{
		len = ft_strlen(msh->bltn[i].cmnd) + j;
		if (!ft_strncmp(cmd.arg[0], msh->bltn[i].cmnd, len))
			return (ft_builtinexecute(cmdnbr, forknbr, msh, i));
		if (i == 1)
			j = 1;
		i++;
	}
	return (-1111);
}
