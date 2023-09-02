/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:28 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/02 04:55:08 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_alias ft_aliastostruct(char *line)
{
	t_alias	aliasstruct;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strncmp(line, "alias ", 6))
		ft_errorexit("Error in ~/.mshrc file", "mshrc", 1);
	aliasstruct.var = ft_calloc(ft_strlen(line), 8);
	aliasstruct.val = ft_calloc(ft_strlen(line), 8);
	while (line[i + 6] && line[i + 6] != '=')
	{
		aliasstruct.var[i] = line[i + 6];
		i++;
	}
	if (line[i + 6] == '\0')
		ft_errorexit("Error in ~/.mshrc file", "mshrc", 1);
	if (line[i + 7] == '\'')
	{
		while (line[i + j + 8] && line[i + j + 8] != '\'')
		{
			aliasstruct.val[j] = line[i + j + 8];
			j++;
		}
	}
	else if (line[i + 7] == '\"')
	{
		while (line[i + j + 8] && line[i + j + 8] != '\"')
		{
			aliasstruct.val[j] = line[i + j + 8];
			j++;
		}
	}
	else
	{
		while (line[i + j + 7] && line[i + j + 7] != ' ')
		{
			aliasstruct.val[j] = line[i + j + 7];
			j++;
		}
	}
	return (aliasstruct);
}

t_alias	*ft_parsemshrc(char **envp)
{
	int		mshrcfile;
	t_alias	*alias;
	char	*line;
	char	*home;
	int		i;

	line = ft_gethome(envp);
	home = ft_strjoin(line, "/.mshrc");
	mshrcfile = open(home, O_RDONLY, 0666);
	free(line);
	alias = ft_calloc(sizeof(t_alias), 100);
	i = 0;
	while (get_next_line(mshrcfile, &line) > 0)
	{
		alias[i] = ft_aliastostruct(line);
		free(line);
		i++;
	}
	alias[i].var = NULL;
	return (alias);
}

t_shell	*ft_initstruct(char **envp)
{
	t_shell	*shell;
	int		shlvlint;
	char	*shlvlstr;

	shell = ft_calloc(sizeof(shell), 10);
	shell->envp = envp;
	shell->alias = ft_parsemshrc(envp);
	shlvlint = ft_atoi(ft_getenvval(shell->envp, "SHLVL"));
	shlvlint++;
	shlvlstr = ft_itoa(shlvlint);
	ft_setenv(shell->envp, "SHLVL", shlvlstr);
	/*ft_setenv(shell->envp, "?", "0"); // segfaults*/
	shell->envpfd = open("/tmp/minishellenvpfile.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_charpptofd(envp, shell->envpfd);
	shell->starttime = ft_gettimems(shell->envp);
	shell->code = 256;
	close(shell->envpfd);
	return (shell);
}
