/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/27 15:28:50 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_testfillfakestruct(t_shell *shell, char *line)
{

	shell->line = line;
	char	**paths;

	paths = ft_getpaths(shell->envp, 1); // This should probably be done somewhere else?
	/*shell->forkamount = 1; //number of fork structs*/
	/*shell->forks = ft_calloc(10 * sizeof(t_forks), 1); //temp calloc*/
	/*shell->forks->cmdamount = 1; //number of command structs*/
	/*shell->forks->cmds = ft_calloc(10 * sizeof(t_cmds), 1); //temp calloc*/
	shell->forks[0].cmds[0].envp = shell->envp; //copy over envp (should be done to every single command struct)
	shell->forks[0].cmds[0].arguments = ft_split(line, ' '); // can be removed as soon as you populate the command struct with the arguments.
	shell->forks[0].cmds[0].absolute = ft_abspathcmd(paths, shell->forks[0].cmds[0].arguments[0]); //can be removed after arguments and absolute are handled by the parser.
	shell->forks[0].cmds[0].detatch = 0; // wether to detach the process (&)
	shell->forks[0].cmds[0].condition = 0; // && || or no condition.
	shell->forks[0].cmds[0].redirect = ft_calloc(10 * sizeof(t_redirect), 1); //temp calloc
	shell->forks[0].cmds[0].redirect[0].fd_in = 0; // in fd make it -1 for heredoc
	shell->forks[0].cmds[0].redirect[0].fd_out = 1; // out fd, 
	shell->forks[0].cmds[0].redirect[0].trc_apd = 1; //trunc append. This is probably completely handled by you, since you open the files and just pass the fd. so it probably doesn't have to be passed to the executioner.
	ft_frearr(paths); //free the temporary paths.
	return (shell);
}

int		ft_countendconditions(char *line, int count, int i)
{
	while (line[i])
	{
		if (line[i] == '&')
		{
			i++;
			count++;
			if (line[i + 1] == '&')
				i++;
		}
		if (line[i] == '|')
		{
			i++;
			count++;
			if (line[i + 1] == '|')
				i++;
		}
		if (line[i] == ';')
		{
			i++;
			count++;
		}
		i++;
	}
	return (count);
}

int ft_parseendcondition(t_shell *shell)
{
	int		icmd;
	int		ifpip;
	int		icpip;

	shell->forks->cmdamount = ft_countendconditions(shell->forks->pipeline, 0, 0) + 1;
	shell->forks->cmds = ft_calloc(10000 * sizeof(t_cmds), 1);
	icmd = 0;
	ifpip = 0;
	icpip = 0;
	while (shell->forks[0].pipeline[ifpip])
	{
		shell->forks->cmds[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;", shell->forks->pipeline[ifpip]))
		{
			shell->forks[0].cmds[icmd].pipeline[icpip] = shell->forks[0].pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		shell->forks[0].cmds[icmd].pipeline[icpip] = '\0';
		if (shell->forks->pipeline[ifpip] == '|')
		{
			ifpip = ifpip + 2;
			shell->forks->cmds[icmd + 1].condition = 2;
		}
		if (!shell->forks[0].pipeline[ifpip])
			return (shell->forks->cmdamount);
		else if (shell->forks->pipeline[ifpip] == '&')
		{
			ifpip++;
			if (shell->forks->pipeline[ifpip] == '&')
			{
				ifpip++;
				shell->forks->cmds[icmd + 1].condition = 1;
			}
			else
				shell->forks->cmds[icmd].detatch = 1;
		}
		if (!shell->forks[0].pipeline[ifpip])
			return (shell->forks->cmdamount);
		else
		{
			ifpip++;
			shell->forks->cmds[icmd + 1].condition = 0;
		}
		icmd++;
	}
	return (shell->forks->cmdamount);
}

void	ft_initstructs(t_shell *shell, int i, int j)
{
	shell->forks[i].cmds = ft_calloc(2000 * 8, sizeof(t_cmds));
	shell->forks[i].cmds[j].envp = shell->envp;
	shell->forks[i].cmds[j].detatch = 0;
	shell->forks[i].cmds[j].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	shell->forks[i].cmds[j].redirect[0].fd_in = 0;
	shell->forks[i].cmds[j].redirect[0].fd_out = 1;
}

void	ft_finalparsing(t_shell *shell, int i, int j)
{
	char	**paths;

	paths = ft_getpaths(shell->envp, 1); // This should probably be done somewhere else?
	shell->forks[i].cmds[j].arguments = ft_split(shell->forks[i].cmds[j].pipeline, ' ');
	shell->forks[i].cmds[j].envp = shell->envp;
	ft_printf("hallo\n");
	ft_printf("%s\n", shell->forks[i].cmds[j].pipeline);
	// CRASHING HERE because pipeline = NULL
	shell->forks[i].cmds[j].absolute = ft_abspathcmd(paths, shell->forks[i].cmds[j].arguments[0]);
	ft_frearr(paths);
}

int	*ft_parseline(char *line, t_shell *shell)
{
	int	i;
	int	j;
	// if (check_quote_closed(line))

	shell->forks = ft_parsepipe(line, shell);
	 /*printf("forkamount: %d\n", shell->forkamount);*/
	 /*printf("split by pip %s\n", shell->forks[0].pipeline);*/
	 /*printf("split by pip %s\n", shell->forks[1].pipeline);*/

	/*shell->forks = ft_parsespchr(shell->forks, shell);*/
	
	i = 0;
	while (shell->forkamount > i) // forks loop should set the cmds.pipeline and set cmds.conditions
	{
	 /*printf("forks loop %d\n", shell->forkamount);*/
		shell->forks[i].cmdamount = ft_parseendcondition(shell);
		j = 0;
	 /*printf("cmdamount: %d\n", shell->forks[i].cmdamount);*/
		while (shell->forks[i].cmdamount > j) // cmds loop should expand, handle redirections and split the pipeline into the arguments
		{
			ft_initstructs(shell, i, j);
			ft_parsevariable(shell->forks[i].cmds[j]); //expanding pipeline
			/*ft_parsewildcard(shell->forks[i].cmds[j]); //expanding pipeline*/
			ft_finalparsing(shell, i, j);
			j++;
		}
		i++;
	}
	/*shell = ft_testfillfakestruct(shell, line); */
	// if (!check_quote_closed(line)) // should probably be done at the beginning since you can't parse a incomplete line.
	return (0);
}


/*
❯ ls | wc
split by pip ls
split by pip  wc
AddressSanitizer:DEADLYSIGNAL
=================================================================
==8345==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000102d8cc35 bp 0x7ffeece79510 sp 0x7ffeece79440 T0)
==8345==The signal is caused by a READ memory access.
==8345==Hint: address points to the zero page.
    #0 0x102d8cc34 in count_str2 exec_strct.c
    #1 0x102d8a37d in ft_parsespchr struct.c:66
    #2 0x102d88eed in ft_parseline parse.c:49
    #3 0x102d86f7c in ft_mainloop main.c:45
    #4 0x102d8739e in main main.c:69
    #5 0x7fff7ba1d3d4 in start (libdyld.dylib:x86_64+0x163d4)

==8345==Register values:
rax = 0x0000000000000000  rbx = 0x00007ffeece79580  rcx = 0x0000100000000000  rdx = 0x0000100000000000
rdi = 0x0000000000000000  rsi = 0x0000100000000000  rbp = 0x00007ffeece79510  rsp = 0x00007ffeece79440
 r8 = 0x0000100000000000   r9 = 0x00000fffffffff00  r10 = 0x0000000000000000  r11 = 0xffffe07113186fc8
r12 = 0x0000000000000000  r13 = 0x0000000000000000  r14 = 0x0000000000000000  r15 = 0x0000000000000000
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV exec_strct.c in count_str2
==8345==ABORTING
zsh: abort      ./minishell


*/
