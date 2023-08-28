/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/28 13:24:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
cmd1: cat < file1 | grep a&&wc -l > file2 > file3
command[1] cat < file1
command[2] grep a&& wc -l > file2 > file3	
command[3] wc -l > file2 > file3	
(for char **argument, cut out the redirection part = only 'cat' or 'wc\n -l')


fork[0] = cat < file1
fork[1] = grep a && wc -l > file2 > file3
fork[0].cmd[0] = cat < file1
fork[1].cmd[0] =  grep a
fork[1].cmd[1] = wc -l ..
*/


t_forks	*ft_parsepipe(char *line, t_shell *shell)
{
	t_forks	*forks;
	char	**tmp;

	shell->forkamount = 1;
	forks = ft_calloc(count_str(line, '|') + 1, sizeof(t_forks)); // does this count the |? so if it is 0 +1 we have 1 fork struct, but we need 2 for null termination?
	if (!forks)
		ft_errorexit("Error allocating memory", "malloc", 1);
	if (!ft_strchr(line, '|'))
		forks[(shell->forkamount) - 1].pipeline = ft_strdup(line);
	else
	{
		tmp = split_not_quote(line, '|');
		while (tmp[(shell->forkamount) - 1])
		{
			forks[(shell->forkamount)-1 ].pipeline = tmp[(shell->forkamount)  - 1];
			shell->forkamount++;
		}
	}
	shell->forks = forks;
	return (forks);
}

		// before split cmd by space, split cmd by &&, ||, (+ &)?
		// then ft_check_redirect needs to happen -> ft_substr take cmd before < > << >>

t_forks	*ft_parsespchr(t_forks *forks, t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	// if (shell->forkamount == 1)
	// 	i = -1;
	while (i < (shell->forkamount))
	{
		/*printf("pipeline = %s\n",forks[i].pipeline );*/
		forks[i].cmds = ft_calloc(count_str2(forks[i].pipeline) + 1, sizeof(t_cmds));
		if (!forks[i].cmds)
			ft_errorexit("Error allocating memory", "malloc", 1);
		tmp = split_spchr(forks[i].pipeline);
		while (tmp[forks[i].cmdamount])
		{
			forks[i].cmds[forks[i].cmdamount].absolute = tmp[forks[i].cmdamount];
			forks[i] = ft_fill_teststrct(forks[i], shell, tmp[forks[i].cmdamount], forks[i].cmdamount);
			forks[i].cmdamount++;
		}
		i++;
	}
	return (forks);
}

t_forks	ft_fill_teststrct(t_forks forks, t_shell *shell, char *cmd, int cmdamount)
{
	char	**paths;

	paths = ft_getpaths(shell->envp, 1);
	forks.cmds[cmdamount].envp = shell->envp;
	forks.cmds[cmdamount].arguments = split_not_quote(cmd, ' '); 
	forks.cmds[cmdamount].absolute = ft_abspathcmd(paths, forks.cmds[cmdamount].arguments[0]); 
	// if (ft_checkcommand(forks.cmds[cmdamount]))
	// 	printf("error\n");
	// printf("abs = %s\n", forks.cmds[cmdamount].absolute);
	forks.cmds[cmdamount].redirect = ft_calloc(10 * sizeof(t_redirect), 1); //temp calloc
	forks.cmds[cmdamount].redirect[0].fd_in = 0; // in fd make it -1 for heredoc
	forks.cmds[cmdamount].redirect[0].fd_out = 1; // out fd, 
	forks.cmds[cmdamount].redirect[0].trc_apd = 1;
	ft_frearr(paths);
	return (forks);
}
