/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   mshrc.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:25:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 04:08:08 by djonker      \___)=(___/                 */
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
		ft_errorexit("Error in ~/.mshrc file, only alias accepted", "mshrc", 1);
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
	free(line);
	free(home);
	alias[i].var = NULL;
	close(mshrcfile);
	return (alias);
}
