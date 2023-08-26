/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/26 16:39:49 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_testfillfakestruct(t_shell *shell, char *line)
{

	shell->line = line;
	char	**paths;

	paths = ft_getpaths(shell->envp, 1); // This should probably be done somewhere else?
	shell->forkamount = 1; //number of fork structs
	shell->forks = ft_calloc(10 * sizeof(t_forks), 1); //temp calloc
	shell->forks->cmdamount = 1; //number of command structs
	shell->forks->cmds = ft_calloc(10 * sizeof(t_cmds), 1); //temp calloc
	shell->forks[0].cmds[0].envp = &shell->envp; //copy over envp (should be done to every single command struct)
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

int	*ft_parseline(char *line, t_shell *shell)
{
	// shell = ft_testfillfakestruct(shell, line); 
	// if (check_quote_closed(line))

	shell->forks = ft_parsepipe(line, shell);
	// printf("forkamount: %d\n", shell->forkamount);
	// printf("split by pip %s\n", shell->forks[0].pipeline);
	// printf("split by pip %s\n", shell->forks[1].pipeline);

	shell->forks = ft_parsespchr(shell->forks, shell);
	
	// This will fill the struct with fake variables, 
	// so if you are testing something just comment out the line in this function,
	// that way you use the variables of your parsing and not the fake ones put in place by the function.
	// if it at least doesn't segfault  the application or mess with other outputs you can leave it be and slowly add all the parsing till you're done :)

	// if (!check_quote_closed(line))
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