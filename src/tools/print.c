/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 00:27:40 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 16:16:45 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printshell(t_shell msh)
{
	printf("\e[1;34mshell struct\e[0;00m\n");
	printf("\e[1;34mline: %s\e[0;00m\n", msh.line);
	printf("\e[1;34mforkamount: %d\e[0;00m\n", msh.forks);
}

void	ft_printforks(t_forks forks, int forknumber)
{
	printf("\e[1;35mforks struct %d\e[0;00m\n", forknumber);
	printf("\e[1;35mpipeline: %s\e[0;00m\n", forks.line);
	printf("\e[1;35mcmdamount: %d\e[0;00m\n", forks.cmds);
}

void	ft_printcommands(t_commands cmd, int cmdnbr, int forknbr)
{
	int		i;

	printf("\e[1;36mcmd struct %d of fork %d\e[0;00m\n", cmdnbr, forknbr);
	printf("\e[1;36mpipeline: %s\e[0;00m\n", cmd.line);
	i = 0;
	while (cmd.arg[i])
	{
		printf("\e[1;36margument %d: %s\e[0;00m\n", i, cmd.arg[i]);
		i++;
	}
	printf("\e[1;36mabsolute: %s\e[0;00m\n", cmd.absolute);
	if (cmd.condition == 1)
		printf("\e[1;36mcondition: &&\e[0;00m\n");
	else if (cmd.condition == 2)
		printf("\e[1;36mcondition: ||\e[0;00m\n");
	else
		printf("\e[1;36mcondition: unconditional\e[0;00m\n");
	if (cmd.prio)
		printf("\e[1;36mcmd gets priority\e[0;00m\n");
	printf("\e[1;36mredirect input from %d files\e[0;00m\n", cmd.infiles);
}

void	ft_printglobs(t_globs globs, char *function)
{
	int	i;

	i = 0;
	printf("\e[1;31mglobs struct in %s\e[0;00m\n", function);
	printf("\e[1;31mpipeline: %s\e[0;00m\n", globs.line);
	printf("\e[1;31mpardir: %s\e[0;00m\n", globs.pardir);
	printf("\e[1;31mgstart: %s\e[0;00m\n", globs.gstart);
	printf("\e[1;31mglob: %c\e[0;00m\n", globs.glob[0]);
	printf("\e[1;31mgend: %s\e[0;00m\n", globs.gend);
	while (globs.subdir[i])
	{
		printf("\e[1;31msubdir %d: %s\e[0;00m\n", i, globs.subdir[i]);
		i++;
	}
	printf("\e[1;31mstart: %s\e[0;00m\n", globs.start);
	printf("\e[1;31mend: %s\e[0;00m\n", globs.end);
}

void	ft_printdup(t_commands cmd, int cmdnbr, int forknbr)
{
	int	i;

	i = 0;
	printf("\e[1;32mdupmachine cmd %d fork %d\e[0;00m\n", cmdnbr, forknbr);
	if (cmdnbr == 0 && forknbr > 0)
		printf("\e[1;32minput from pipe\e[0;00m\n");
	else if (cmd.infiles)
		printf("\e[1;32minput from %d files\e[0;00m\n", cmd.infiles);
	else
		printf("\e[1;32minput from stdin\e[0;00m\n");
	if (cmdnbr + 1 == cmd.cmds && forknbr + 1 < cmd.forks)
		printf("\e[1;32moutput to pipe\e[0;00m\n");
	else if (cmd.ofi[0])
	{
		while (cmd.ofi[i])
		{
			if (cmd.append[i])
				printf("\e[1;36moutput %d append: %s\e[0;00m\n", i, cmd.ofi[i]);
			else
				printf("\e[1;36moutput %d trunct: %s\e[0;00m\n", i, cmd.ofi[i]);
			i++;
		}
	}
	else
		printf("\e[1;32moutput to stdout\e[0;00m\n");
}
