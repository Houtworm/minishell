/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_2.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/25 04:39:53 by houtworm     \___)=(___/                 */
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

/*t_forks	*ft_forks_strct(char *line, t_shell *shell)*/
/*{*/
	/*t_forks	*forks;*/
	/*char	**tmp;*/
	/*int		i;*/

	/*forks = ft_calloc(count_str(line, '|') + 1, sizeof(t_forks));*/
	/*if (!forks)*/
		/*return (NULL);	//ft_error()?;*/
	/*tmp = split_not_quote(line, '|');*/
	/*i = 0;*/
	/*while (tmp[i])*/
	/*{*/
		/*forks[i].per_pip = tmp[i];*/
		/*forks[i].commands = ft_exec_strct(forks[i].per_pip, shell);*/
		/*i++;*/
	/*}*/
	/*return (forks);*/
/*}*/

/*t_cmd	*ft_exec_strct(char *per_pip, t_shell *shell)*/
/*{*/
	/*t_cmd	*cmd;*/
	/*char	**paths;*/
	/*int		i;*/
	/*int		k;*/

	/*printf("%d str in %s\n",count_str2(per_pip), per_pip);*/
	/*cmd = ft_calloc(count_str2(per_pip) + 1, sizeof(t_cmd));*/
	/*if (!cmd)*/
		/*return (NULL);	//ft_error()?;*/
	/*i = 0;*/
	/*while (i < count_str2(per_pip))*/
	/*{*/
		/*k = 0;*/
		/*while (per_pip[k])*/
		/*{*/
			/*if (s[i] == '&' && s[i] == '|' || s[i] == ';')*/
				/*cmd[i].tmp = ft_substr(per_pip, );*/
			
		/*}*/
	/*}*/

// if there is no simbols in per_pip, then create one cmd struct
// if there is &&, ||, &, ;, split(remove the character) and create cmd struct for each

/*}*/



void	ft_strct_per_cmd(char **command, t_shell *shell)
{
	t_cmds	*cmds;
	char	**paths;
	int		i;

	cmds = ft_calloc(count_str(shell->line, '|') + 1, sizeof(t_cmds));
	if (!cmds)
		return ;	//ft_error()?; (There is a ft_errorexit function :)
	i = 0;
	paths = ft_getpaths(shell->envp, 1);
	while (command[i])
	{
		// before split cmd by space, split cmd by &&, ||, (+ &)?
		// then ft_check_redirect needs to happen -> ft_substr take cmd before < > << >>
		// 
		ft_check_redirect(cmds[i], command[i]);
		cmds[i].arguments = split_not_quote(command[i], ' ');
		cmds[i].absolute = ft_abspathcmd(paths, cmds[i].arguments[0]);
		printf("%s\n", cmds[i].absolute);
		i++;
	}
	shell->forks->cmds = cmds;
	ft_frearr(paths);
	// ft_check_redirect(shell->forks->cmds, i);
}
