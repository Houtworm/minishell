/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 03:50:51 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/04 03:26:31 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long long	ft_gettimems(char **envp)
{
	char		*date;
	long long	currenttime;

	date = ft_system("date +%s%3N", envp);
	currenttime = ft_atol(date);
	free(date);
	return (currenttime);
}

void	ft_printshell(t_shell shell)
{
	printf("\e[1;34mshell struct\e[0;00m\n");
	printf("\e[1;34mforkamount: %d\e[0;00m\n", shell.forkamount);
	printf("\e[1;34mline: %s\e[0;00m\n", shell.line);
}

void	ft_printforks(t_forks forks, int forknumber)
{
	printf("\e[1;35mforks struct %d\e[0;00m\n", forknumber);
	printf("\e[1;35mpipeline: %s\e[0;00m\n", forks.pipeline);
	printf("\e[1;35mcmdamount: %d\e[0;00m\n", forks.cmdamount);
}

void	ft_printcmds(t_cmds cmds, int cmdnbr)
{
	int		i;

	i = 0;
	printf("\e[1;36mcmds struct %d\e[0;00m\n", cmdnbr);
	printf("\e[1;36mpipeline: %s\e[0;00m\n", cmds.pipeline);
	while (cmds.arguments[i])
	{
		printf("\e[1;36margument %d: %s\e[0;00m\n", i, cmds.arguments[i]);
		i++;
	}
	printf("\e[1;36mabsolute: %s\e[0;00m\n", cmds.absolute);
	 printf("\e[1;36mcondition: %d\e[0;00m\n", cmds.condition);
	 printf("\e[1;36mdetatch: %d\e[0;00m\n", cmds.detatch);
	 printf("\e[1;36mredirect->infilename: %s\e[0;00m\n", cmds.redirect->infilename);
	 printf("\e[1;36mredirect->outfilename: %s\e[0;00m\n", cmds.redirect->outfilename);
	 printf("\e[1;36mredirect->delimiter: %s\e[0;00m\n", cmds.redirect->delimiter);
	 printf("\e[1;36mredirect->append: %d\e[0;00m\n", cmds.redirect->append);

}

void	ft_printglobs(t_globs globs, char *function)
{
	printf("\e[1;31mglobs struct in %s\e[0;00m\n", function);
	printf("\e[1;31mgstart: %s\e[0;00m\n", globs.gstart);
	printf("\e[1;31mgend: %s\e[0;00m\n", globs.gend);
	printf("\e[1;31mperiod: %d\e[0;00m\n", globs.period);
	printf("\e[1;31mstart: %s\e[0;00m\n", globs.start);
	printf("\e[1;31mglob: %s\e[0;00m\n", globs.glob);
	printf("\e[1;31mend: %s\e[0;00m\n", globs.end);
	printf("\e[1;31msubdir: %s\e[0;00m\n", globs.subdir);
	printf("\e[1;31mpardir: %s\e[0;00m\n", globs.pardir);
	printf("\e[1;31mmatches: %s\e[0;00m\n", globs.matches);
	printf("\e[1;31mpipeline: %s\e[0;00m\n", globs.pipeline);
}
