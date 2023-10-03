/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/03 17:39:35 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_removequotes(char **args)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	char	quote;

	i = 0;
	while (args[i])
		i++;
	new = ft_calloc(i + 1, 8);
	i = 0;
	while (args[i])
	{
		new[i] = ft_calloc(100, 8);
		j = 0;
		k = 0;
		while (args[i][j])
		{
			while (args[i][j] && args[i][j] != '\'' && args[i][j] != '\"')
			{
				new[i][k] = args[i][j];
				/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
				j++;
				k++;
			}
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				quote = args[i][j];
				/*printf("skipping quote %c\n", quote);*/
				j++;
				while (args[i][j] && args[i][j] != quote)
				{
					new[i][k] = args[i][j];
					/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
					j++;
					k++;
				}
				/*printf("closing quote %c\n", quote);*/
				j++;
			}
		}
		new[i][k] = '\0';
		/*printf("i: %d, j: %d %c k: %d %c\n", i, j, args[i][j], k, new[i][k]);*/
		i++;
	}
	ft_frearr(args);
	/*new[i] = ft_calloc(2, 8);*/
	new[i] = NULL;
	return (new);
}

char	**ft_splitcmd(char *cmd)
{
	char	**arguments;
	int		icmd;
	int		arg;
	int		iarg;

	icmd = 0;
	arg = 1;
	while (cmd[icmd])
	{
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'')
			{
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\'')
					icmd++;
			}
			if (cmd[icmd] == '\"')
			{
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\"')
					icmd++;
			}
			if (cmd[icmd])
				icmd++;
		}
		while (cmd[icmd] == ' ')
			icmd++;
		arg++;
	}
	arguments = ft_calloc(arg + 1, 8);
	icmd = 0;
	arg = 0;
	while (cmd[icmd] == ' ')
		icmd++;
	while (cmd[icmd])
	{
		arguments[arg] = ft_calloc(100, 8);
		iarg = 0;
		while (cmd[icmd] && cmd[icmd] != ' ')
		{
			if (cmd[icmd] == '\'')
			{
				arguments[arg][iarg] = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\'')
				{
					arguments[arg][iarg] = cmd[icmd];
					iarg++;
					icmd++;
				}
			}
			else if (cmd[icmd] == '\"')
			{
				arguments[arg][iarg] = cmd[icmd];
				iarg++;
				icmd++;
				while (cmd[icmd] && cmd[icmd] != '\"')
				{
					arguments[arg][iarg] = cmd[icmd];
					iarg++;
					icmd++;
				}
			}
			arguments[arg][iarg] = cmd[icmd];
			iarg++;
			icmd++;
		}
		arguments[arg][iarg] = '\0';
		while (cmd[icmd] == ' ')
			icmd++;
		arg++;
	}
	arguments[arg] = NULL;
	return (arguments);
}

void	ft_parsetilde(t_cmds *cmds, t_shell shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*temp;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmds->pipeline) + 1), 8);
	rest = ft_calloc((ft_strlen(cmds->pipeline) + 1), 8);
	i = 0;
	while (cmds->pipeline[i])
	{
		j = 0;
		while (cmds->pipeline[i] && cmds->pipeline[i] != '~')
		{
			if (cmds->pipeline[i] == '\'')
			{
				begin[j] = cmds->pipeline[i];
				i++;
				j++;
				while (cmds->pipeline[i] && cmds->pipeline[i] != '\'')
				{
					begin[j] = cmds->pipeline[i];
					i++;
					j++;
				}
			}
			else if (cmds->pipeline[i] == '\"')
			{
				begin[j] = cmds->pipeline[i];
				i++;
				j++;
				while (cmds->pipeline[i] && cmds->pipeline[i] != '\"')
				{
					begin[j] = cmds->pipeline[i];
					i++;
					j++;
				}
			}
			begin[j] = cmds->pipeline[i];
			i++;
			j++;
		}
		if (cmds->pipeline[i] == '~')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (cmds->pipeline[i])
			{
				rest[j] = cmds->pipeline[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(cmds->pipeline);
			temp = ft_gethome(shell.envp);
			if (temp == NULL)
				cmds->pipeline = ft_strjoin(begin, rest);
			else
				cmds->pipeline = ft_vastrjoin(3, begin, temp, rest);
			i = 0;
			free(temp);
		}
	}
	ft_vafree(2, begin, rest);
}

t_shell *ft_parsecmds(t_shell *shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell->forks[forknumber].cmds[cmdnumber].envp = shell->envp;
	shell->forks[forknumber].cmds[cmdnumber].debug = shell->debug;
	shell->forks[forknumber].cmds[cmdnumber].forkamount = shell->forkamount;
	shell->forks[forknumber].cmds[cmdnumber].prio = ft_priority(shell->forks[forknumber].cmds, cmdnumber); //0;
	ft_parsealiases(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsevariable(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsetilde(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_executepriority(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseredirection(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseglobs(&shell->forks[forknumber].cmds[cmdnumber]); //should be moved to ft_parseline()
	paths = ft_splitcmd(shell->forks[forknumber].cmds[cmdnumber].pipeline);
	shell->forks[forknumber].cmds[cmdnumber].arguments = ft_removequotes(paths);
	/*shell->forks[forknumber].cmds[cmdnumber].arguments = split_not_quote(shell->forks[forknumber].cmds[cmdnumber].pipeline, ' ');*/
	/*shell->forks[forknumber].cmds[cmdnumber].arguments = ft_checkarg(shell->forks[forknumber].cmds[cmdnumber].arguments, 0);*/
	if (!shell->forks[forknumber].cmds[cmdnumber].arguments[0])
	{
		shell->stop = 1;
		return (shell);
	}
	shell->forks[forknumber].cmds[cmdnumber].cmdamount = shell->forks[forknumber].cmdamount;
	paths = ft_getpaths(shell->envp, 1);
	shell->forks[forknumber].cmds[cmdnumber].absolute = ft_abspathcmd(paths, shell->forks[forknumber].cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
	return (shell);
}


char	*ft_parseoldline(char *line, t_shell *shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*rest;

	begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] && (line[i] != '!' || line[i + 1] != '!'))
		{
			if (line[i] == '\'')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\'')
				{
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			begin[j] = line[i];
			i++;
			j++;
		}
		if (line[i] == '!' && line[i + 1] == '!')
		{
			if (!shell->oldline[0])
				return (NULL);
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (line[i])
			{
				rest[j] = line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free (line);
			line = ft_vastrjoin(3, begin, shell->oldline, rest);
			i = 0;
		}
	}
	ft_vafree(2, begin, rest);
	return (line);
}

int	ft_parseline(char *line, t_shell *shell)
{
	int	forknumber;

	if (ft_startsyntax(shell, line))
		return (2);
	/*line = ft_closeline(line);*/
	/*line = ft_completeline(line, 0);*/
	while (check_quote_closed(line))
	{
		line = ft_closeline(line);
		line = ft_completeline(line, 0);
	}
	/*line = ft_parseoldline(line, shell);*/
	/*if (!line)*/
		/*return (127);*/
	/*free(shell->oldline);*/
	shell->oldline = ft_strdup(line);
	line = ft_parsehashtag(line);
	if (line[0] == '\0')
		return (1);
	if (ft_checksyntax(shell, line))
		return (2);
	*shell = ft_parsepipe(line, *shell);
	if (shell->debug)
		ft_printshell(*shell);
	forknumber = 0;
	while (shell->forkamount > forknumber)
	{
		shell->forks[forknumber] = ft_parseendcondition(shell->forks[forknumber]);
		shell->forks[forknumber] = ft_parseheredoc(shell->forks[forknumber], shell->forks[forknumber].cmdamount);
		if (shell->debug)
			ft_printforks(shell->forks[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
