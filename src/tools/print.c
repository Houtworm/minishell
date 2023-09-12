/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 00:27:40 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/12 11:35:51 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printshell(t_shell shell)
{
	printf("\e[1;34mshell struct\e[0;00m\n");
	printf("\e[1;34mline: %s\e[0;00m\n", shell.line);
	printf("\e[1;34mforkamount: %d\e[0;00m\n", shell.forkamount);
}

void	ft_printforks(t_forks forks, int forknumber)
{
	printf("\e[1;35mforks struct %d\e[0;00m\n", forknumber);
	printf("\e[1;35mpipeline: %s\e[0;00m\n", forks.pipeline);
	printf("\e[1;35mcmdamount: %d\e[0;00m\n", forks.cmdamount);
}

void	ft_printredirect(t_redirect *redirect)
{
	int	i;

	i = 0;
	while (redirect[i].infilename)
	{
		printf("\e[1;36mredirect %d input from file: %s\e[0;00m\n", i, redirect[i].infilename);
		i++;
	}
	i = 0;
	while (redirect[i].outfilename)
	{
		if (redirect[i].append)
			printf("\e[1;36mredirect %d output appended to: %s \e[0;00m\n", i, redirect[i].outfilename);
		else
			printf("\e[1;36mredirect %d output trunctuating: %s \e[0;00m\n", i, redirect[i].outfilename);
		i++;
	}
	i = 0;
	while (redirect[i].delimiter)
	{
		printf("\e[1;36mredirect %d input from heredoc with delimiter: %s\e[0;00m\n", i + 1, redirect[i].delimiter);
		i++;
	}
}

void	ft_printcmds(t_cmds cmds, int cmdnbr, int forknbr)
{
	int		i;

	printf("\e[1;36mcmds struct %d of fork %d\e[0;00m\n", cmdnbr, forknbr);
	printf("\e[1;36mpipeline: %s\e[0;00m\n", cmds.pipeline);
	i = 0;
	while (cmds.arguments[i])
	{
		printf("\e[1;36margument %d: %s\e[0;00m\n", i, cmds.arguments[i]);
		i++;
	}
	printf("\e[1;36mabsolute: %s\e[0;00m\n", cmds.absolute);
	if (cmds.condition == 1)
		printf("\e[1;36mcondition: &&\e[0;00m\n");
	else if (cmds.condition == 2)
		printf("\e[1;36mcondition: ||\e[0;00m\n");
	else
		printf("\e[1;36mcondition: unconditional\e[0;00m\n");
	if (cmds.detatch)
		printf("\e[1;36mprogram will detatch\e[0;00m\n");
	ft_printredirect(cmds.redirect);
}

void	ft_printglobs(t_globs globs, char *function)
{
	int	i;

	i = 0;
	printf("\e[1;31mglobs struct in %s\e[0;00m\n", function);
	printf("\e[1;31mpipeline: %s\e[0;00m\n", globs.pipeline);
	printf("\e[1;31mpardir: %s\e[0;00m\n", globs.pardir);
	printf("\e[1;31mgstart: %s\e[0;00m\n", globs.gstart);
	printf("\e[1;31mglob: %c\e[0;00m\n", globs.glob);
	printf("\e[1;31mgend: %s\e[0;00m\n", globs.gend);
	while (globs.subdir[i])
	{
		printf("\e[1;31msubdir %d: %s\e[0;00m\n", i, globs.subdir[i]);
		i++;
	}
	printf("\e[1;31mperiod: %d\e[0;00m\n", globs.period);
	printf("\e[1;31mstart: %s\e[0;00m\n", globs.start);
	printf("\e[1;31mend: %s\e[0;00m\n", globs.end);
	printf("\e[1;31mmatches: %s\e[0;00m\n", globs.matches);
}

void	ft_printdup(t_cmds cmds, int cmdnbr, int forknbr)
{
	printf("\e[1;32mdupmachine cmd %d fork %d\e[0;00m\n", cmdnbr, forknbr);
	if (cmdnbr == 0 && forknbr > 0)
		printf("\e[1;32minput from pipe\e[0;00m\n");
	else if (cmds.redirect[0].hdfd > 0)
		printf("\e[1;32minput from heredoc\e[0;00m\n");
	else if (cmds.redirect[0].infilename)
		printf("\e[1;32minput from file %s\e[0;00m\n", cmds.redirect[0].infilename);
	else
		printf("\e[1;32minput from stdin\e[0;00m\n");
	if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount)
		printf("\e[1;32moutput to pipe\e[0;00m\n");
	else if (cmds.redirect[0].outfilename)
		printf("\e[1;32moutput to file %s\e[0;00m\n", cmds.redirect[0].outfilename);
	else
		printf("\e[1;32moutput to stdout\e[0;00m\n");
}
