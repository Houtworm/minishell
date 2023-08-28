/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/27 22:33:10 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_initstructs(t_shell *shell, int i, int j)
{
	shell->forks[i].cmds = ft_calloc(2000 * 8, sizeof(t_cmds));
	shell->forks[i].cmds[j].envp = shell->envp;
	shell->forks[i].cmds[j].detatch = 0;
	shell->forks[i].cmds[j].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	shell->forks[i].cmds[j].redirect[0].fd_in = 0;
	shell->forks[i].cmds[j].redirect[0].fd_out = 1;
}

void	ft_finalparsing(t_forks *forks, int i, int j)
{
	char	**paths;

	paths = ft_getpaths(forks->cmds[0].envp, 1); // This should probably be done somewhere else?
	forks[i].cmds[j].arguments = ft_split(forks[i].cmds[j].pipeline, ' ');
	ft_printf("%s\n", forks[i].cmds[j].pipeline);
	// CRASHING HERE because pipeline = NULL
	forks[i].cmds[j].absolute = ft_abspathcmd(paths, forks[i].cmds[j].arguments[0]);
	ft_frearr(paths);
}

int	ft_parseline(char *line, t_shell shell)
{
	int	i;
	int	j;
	// if (check_quote_closed(line))

	shell.forks = ft_parsepipe(line, &shell);
	 printf("forkamount: %d\n", shell.forkamount);
	 /*printf("split by pip %s\n", shell.forks[0].pipeline);*/
	 /*printf("split by pip %s\n", shell.forks[1].pipeline);*/

	/*shell->forks = ft_parsespchr(shell->forks, shell);*/
	
	i = 0;
	while (shell.forkamount > i) // forks loop should set the cmds.pipeline and set cmds.conditions
	{
		/*printf("forks loop %d\n", shell->forkamount);*/
		*shell.forks = ft_parseendcondition(*shell.forks);
		j = 0;
		/*printf("cmdamount: %d\n", shell->forks[i].cmdamount);*/
		while (shell.forks[i].cmdamount > j) // cmds loop should expand, handle redirections and split the pipeline into the arguments
		{
			ft_initstructs(&shell, i, j);
			ft_parsevariable(shell.forks[i].cmds[j]); //expanding pipeline
			/*ft_parsewildcard(shell.forks[i].cmds[j]); //expanding pipeline*/
			ft_finalparsing(shell.forks, i, j);
			j++;
		}
		i++;
	}
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
