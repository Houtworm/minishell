/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/26 12:08:34 by yitoh         ########   odam.nl         */
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

	forks = ft_calloc(count_str(line, '|') + 1, sizeof(t_forks));
	if (!forks)
		ft_errorexit("Error allocating memory", "malloc", 1);
	tmp = split_not_quote(line, '|');
	while (tmp[shell->forkamount])
	{
		forks[shell->forkamount].pipeline = tmp[shell->forkamount];
		shell->forkamount++;
	}
	ft_frearr(tmp);
	return (forks);
}


t_forks	*ft_parsespchr(t_forks *forks, t_shell *shell)
{
	char	**tmp;
	int		i;
	int		k;

	i = 0;
	while (i < shell->forkamount)
	{
		forks[i].cmds = ft_calloc(count_str2(forks[i].pipeline) + 1, sizeof(t_cmds));
		if (!forks[i].cmds)
			ft_errorexit("Error allocating memory", "malloc", 1);
		tmp = split_spchr(forks[i].pipeline);
		while (tmp[forks[i].cmdamount])
		{
			printf("split by spchr %s\n", tmp[forks[i].cmdamount]);
			forks[i].cmds[forks[i].cmdamount].absolute = tmp[forks[i].cmdamount];
			forks[i].cmdamount++;
		}
		ft_frearr(tmp);
		i++;
	}
	return (forks);
}

/////////////////////////

// t_forks	*ft_forks_strct(char *line, t_shell *shell)
// {
// 	t_forks	*forks;
// 	char	**tmp;
// 	int		i;

// 	forks = ft_calloc(count_str(line, '|') + 1, sizeof(t_forks));
// 	if (!forks)
// 		ft_errorexit("Error allocating memory", "malloc", 1);
// 	tmp = split_not_quote(line, '|');
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		forks[i].pipeline = tmp[i];
// 		forks[i].cmds = ft_exec_strct(forks[i].pipeline, forks[i]);
// 		i++;
// 		shell->forkamount++;
// 	}
// 	ft_frearr(tmp);
// 	return (forks);
// }

// t_cmds	*ft_exec_strct(char *pipeline, t_forks forks)
// {
// 	t_cmds	*cmd;
// 	char	**tmp;
// 	// char	**paths;
// 	int		i;

// 	// printf("%d str in %s\n", count_str2(pipeline), pipeline);
// 	forks.cmdamount = count_str2(pipeline);
// 	cmd = ft_calloc(forks.cmdamount + 1, sizeof(t_cmds));
// 	if (!cmd)
// 		ft_errorexit("Error allocating memory", "malloc", 1);
// 	tmp = split_spchr(pipeline);
// 	i = 0;
// 	while (i < forks.cmdamount)
// 	{
// 		printf("split by spchr %s\n", tmp[i]);
// 		cmd[i].absolute = tmp[i];
// 		i++;
// 	}
// 	ft_frearr(tmp);
// 	return (cmd);
// // if there is no simbols in pipeline, then create one cmd struct
// // if there is &&, ||, &, ;, split(remove the character) and create cmd struct for each

// }



// void	ft_strct_per_cmd(char **command, t_shell *shell)
// {
// 	t_cmds	*cmds;
// 	char	**paths;
// 	int		i;

// 	cmds = ft_calloc(count_str(shell->line, '|') + 1, sizeof(t_cmds));
// 	if (!cmds)
// 		ft_errorexit("Error allocating memory", "malloc", 1);
// 	i = 0;
// 	paths = ft_getpaths(shell->envp, 1);
// 	while (command[i])
// 	{
// 		// before split cmd by space, split cmd by &&, ||, (+ &)?
// 		// then ft_check_redirect needs to happen -> ft_substr take cmd before < > << >>
// 		ft_check_redirect(cmds[i], command[i]);
// 		cmds[i].arguments = split_not_quote(command[i], ' ');
// 		cmds[i].absolute = ft_abspathcmd(paths, cmds[i].arguments[0]);
// 		printf("%s\n", cmds[i].absolute);
// 		i++;
// 	}
// 	shell->forks->cmds = cmds;
// 	ft_frearr(paths);
// 	// ft_check_redirect(shell->forks->cmds, i);
// }
