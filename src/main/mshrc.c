/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mshrc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:25:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:05 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_setaliasvar(t_alias *alias, char *line, int i)
{
	while (line[i + 6] && line[i + 6] != '=')
	{
		alias->var[i] = line[i + 6];
		i++;
	}
	if (line[i + 6] == '\0')
		ft_errorexit("Error in ~/.mshrc file", "mshrc", 1);

	return (i);
}

void	ft_setaliasval(t_alias *alias, char *line, int i)
{
	char	quote;
	int		j;

	j = 0;
	if (line[i + 7] == '\'' || line[i + 7] == '\"')
	{
		quote = line[i + 7];
		while (line[i + j + 8] && line[i + j + 8] != quote)
		{
			alias->val[j] = line[i + j + 8];
			j++;
		}
	}
	else
	{
		while (line[i + j + 7] && line[i + j + 7] != ' ')
		{
			alias->val[j] = line[i + j + 7];
			j++;
		}
	}
}

t_alias ft_aliastostruct(char *line)
{
	t_alias	aliasstruct;
	int		i;

	i = 0;
	if (ft_strncmp(line, "alias ", 6))
		ft_errorexit("Error in ~/.mshrc file, only alias accepted", "mshrc", 1);
	aliasstruct.var = ft_calloc(ft_strlen(line), 8);
	aliasstruct.val = ft_calloc(ft_strlen(line), 8);
	i = ft_setaliasvar(&aliasstruct, line, i);
	ft_setaliasval(&aliasstruct, line, i);
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
	ft_vafree(2, line, home);
	alias[i].var = NULL;
	close(mshrcfile);
	return (alias);
}
