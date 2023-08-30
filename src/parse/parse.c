/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/30 09:20:32 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_setcmddefaults(t_shell shell, int forknumber, int cmdnumber)
{
	shell.forks[forknumber].cmds[cmdnumber].envp = shell.envp;
	shell.forks[forknumber].cmds[cmdnumber].detatch = 0;
	shell.forks[forknumber].cmds[cmdnumber].forkamount = shell.forkamount;
	shell.forks[forknumber].cmds[cmdnumber].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	/*shell.forks[forknumber].cmds[cmdnumber].redirect[0].fd_in = 0;*/
	/*shell.forks[forknumber].cmds[cmdnumber].redirect[0].fd_out = 1;*/
}

void	ft_finalparsing(t_forks forks, int cmdnumber)
{
	char	**paths;

	paths = ft_getpaths(forks.cmds[0].envp, 1);
	forks.cmds[cmdnumber].arguments = split_not_quote(forks.cmds[cmdnumber].pipeline, ' ');
	forks.cmds[cmdnumber].cmdamount = forks.cmdamount;
	// forks.cmds[cmdnumber].arguments = ft_split(forks.cmds[cmdnumber].pipeline, ' ');
	forks.cmds[cmdnumber].absolute = ft_abspathcmd(paths, forks.cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
}


t_shell ft_parsecmds(t_shell shell, int forknumber, int cmdnumber)
{
	ft_setcmddefaults(shell, forknumber, cmdnumber);
	ft_parsevariable(shell.forks[forknumber].cmds[cmdnumber]); //expanding pipeline
	/*ft_parsewildcard(shell.forks[forknumber].cmds[cmdnumber]); //expanding pipeline*/
	ft_finalparsing(shell.forks[forknumber], cmdnumber);
	return (shell);
}

char	*ft_closequote(char *line)
{
	int		quote;
	char	*temp;
	int		ret;
	char	*gnl;

	quote = check_quote_closed(line);
	if (quote)
	{
		ret = get_next_line(0, &gnl);
		
		

		free(line);
		return (temp);
	}
	return (line);
}

t_shell	ft_parseline(char *line, t_shell shell)
{
	int	forknumber;
	int	cmdnumber;
	// if (check_quote_closed(line))
	line = ft_closequote(line);
	shell = ft_parsepipe(line, shell);
	/*shell->forks = ft_parsespchr(shell->forks, shell);*/
	/*ft_printshell(shell); // printing contents of shellstruct*/
	forknumber = 0;
	while (shell.forkamount > forknumber)
	{
		shell.forks[forknumber] = ft_parseendcondition(shell.forks[forknumber]);
		/*ft_printforks(shell.forks[forknumber], forknumber); //printing contents of forkstruct*/
		cmdnumber = 0;
		while (shell.forks[forknumber].cmdamount > cmdnumber)
		{
			shell = ft_parsecmds(shell, forknumber, cmdnumber);
			/*ft_printcmds(shell.forks[forknumber].cmds[cmdnumber], cmdnumber); // printing content of cmdstruct*/
			cmdnumber++;
		}
		forknumber++;
	}
	return (shell);
}
