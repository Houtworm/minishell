/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/03 06:29:50 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsewildcard(t_cmds cmd)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;

	curdir = ft_getpwd(cmd.envp, 0);
	ft_printf("current directory: %s\n", curdir);
	dir = opendir(curdir); // needs to run for every sub directory.
	while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
	{

		ft_printf("d_name: %s\n", dirents->d_name);
	}
	return (cmd.pipeline);
}

int	ft_parseglobs(t_cmds cmd)
{
	char			*globstart;
	char			*globend;
	int				i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	globstart = ft_calloc(ft_strlen(cmd.pipeline), 8);
	globend = ft_calloc(ft_strlen(cmd.pipeline), 8);
	while (cmd.pipeline[i + j + k]) // loop to search for the glob to parse
	{
		k = 0;
		if (cmd.pipeline[i + j] == '\'') // ignore single quote
		{
			j++;
			while (cmd.pipeline[i + j] != '\'')
			{
				globstart[j] = cmd.pipeline[i + j];
				j++;
			}
			j++;
		}
		if (cmd.pipeline[i + j] == '\"') // ignore double quote
		{
			j++;
			while (cmd.pipeline[i + j] != '\"')
			{
				globstart[j] = cmd.pipeline[i + j]; // do include characters to possible glob
				j++;
			}
			j++;
		}
		if (cmd.pipeline[i + j] == ' ') // moving on to the next possible glob
		{
			i = i + j + 1;
			j = 0;
		}
		if (cmd.pipeline[i + j] == '*') // wildcard hit
		{
			j++;
			while (cmd.pipeline[i + j + k] && !ft_strchr(" /", cmd.pipeline[i + j]))
			{
				globend[k] = cmd.pipeline[i + j + k];
				k++;
			}
			j++;
			cmd.pipeline = ft_parsewildcard(cmd);
		}
		/*if (cmd.pipeline[i + j + k] == '?') // joker hit*/
		/*if (cmd.pipeline[i + j + k] == '[') // option hit*/
		globstart[j] = cmd.pipeline[i + j + k];
		j++;
	}
	return (0);
}
// . and .. might be a problem.
