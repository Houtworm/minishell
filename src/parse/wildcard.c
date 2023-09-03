/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/03 09:30:43 by houtworm     \___)=(___/                 */
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
	dir = opendir(curdir); // needs to run for every sub directory.
	matches = NULL;
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
				matches = ft_vastrjoin(3, matches, dirents->d_name, " ");
			}
		}
	}
	if (!matches)
		return (cmd.pipeline);
	return (matches);
}
