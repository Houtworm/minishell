/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/03 08:24:18 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsewildcard(t_cmds cmd, char *globstart, char *globend)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	int				i;
	int				j;
	char			*matches;

	curdir = ft_getpwd(cmd.envp, 1);
	/*ft_printf("current directory: %s\n", curdir);*/
	dir = opendir(curdir); // needs to run for every sub directory.
	matches = NULL;
	/*printf("globstart: %s\nglobend: %s\n", globstart, globend);*/
	while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
	{
		if (!ft_strncmp(dirents->d_name, globstart, ft_strlen(globstart))) // if start of glob matches
		{
			/*printf("%s* start matches with %s\n", globstart, dirents->d_name);*/
			i = ft_strlen(globend);
			j = ft_strlen(dirents->d_name);
			while (i && j && globend[i] == dirents->d_name[j]) //while characters match from the end
			{
				i--;
				j--;
			}
			if (i == 0 && globend[i] == dirents->d_name[j])// if first character of glob end matches
			{
				/*printf("*%s end matches with %s\n", globend, dirents->d_name);*/
				matches = ft_vastrjoin(4, matches, curdir, dirents->d_name, " ");
			}
			/*else // no match*/
				/*printf("no match with dir: %s\n", dirents->d_name);*/
		}
		/*else // no match*/
			/*printf("no match with dir: %s\n", dirents->d_name);*/
	}
	/*ft_printf("matches: %s\n", matches);*/

	return (matches);
}

int	ft_parseglobs(t_cmds *cmd)
{
	char			*globstart;
	char			*globend;
	int				i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	globstart = ft_calloc(ft_strlen(cmd->pipeline), 8);
	globend = ft_calloc(ft_strlen(cmd->pipeline), 8);
	while (cmd->pipeline[i + j + k]) // loop to search for any glob to parse
	{
		k = 0;
		if (cmd->pipeline[i + j] == '\'') // ignore single quote
		{
			j++;
			while (cmd->pipeline[i + j] != '\'')
			{
				globstart[j] = cmd->pipeline[i + j]; // do include beginning of glob ignoring quotes
				j++;
			}
			j++;
		}
		if (cmd->pipeline[i + j] == '\"') // ignore double quote
		{
			j++;
			while (cmd->pipeline[i + j] != '\"')
			{
				globstart[j] = cmd->pipeline[i + j]; // do include beginning of glob ignoring quotes
				j++;
			}
			j++;
		}
		if (cmd->pipeline[i + j] == ' ') // moving on to the next possible glob
		{
			i = i + j + 1;
			j = 0;
		}
		if (cmd->pipeline[i + j] == '*') // wildcard hit
		{
			globstart[j] = '\0';
			j++;
			while (cmd->pipeline[i + j + k] && !ft_strchr(" /", cmd->pipeline[i + j])) // while we are not at the end of the possible glob
			{
				globend[k] = cmd->pipeline[i + j + k];
				k++;
			}
			globend[k] = '\0';
			j++;
			cmd->pipeline = ft_vastrjoin(3, ft_substr(cmd->pipeline, 0, i), ft_parsewildcard(*cmd, globstart, globend), cmd->pipeline[i + j + k]);
		}
		/*if (cmd->pipeline[i + j + k] == '?') // joker hit*/
		/*{*/
			/*j++;*/
			/*while (cmd->pipeline[i + j + k] && !ft_strchr(" /", cmd->pipeline[i + j])) // while we are not at the end of the possible glob*/
			/*{*/
				/*globend[k] = cmd->pipeline[i + j + k];*/
				/*k++;*/
			/*}*/
			/*j++;*/
			/*cmd->pipeline = ft_parsequestionmark(cmd, globstart, globend, i + j + k);*/
		/*}*/
		/*if (cmd->pipeline[i + j + k] == '[') // option hit*/
		/*{*/
			/*j++;*/
			/*while (cmd->pipeline[i + j + k] && !ft_strchr(" /", cmd->pipeline[i + j])) // while we are not at the end of the possible glob*/
			/*{*/
				/*globend[k] = cmd->pipeline[i + j + k];*/
				/*k++;*/
			/*}*/
			/*j++;*/
			/*cmd->pipeline = ft_parsesquarebrack(cmd, globstart, globend, i + j + k);*/
		/*}*/
		globstart[j] = cmd->pipeline[i + j + k];
		j++;
	}
	/*printf("%s\n", cmd->pipeline);*/
	return (0);
}
