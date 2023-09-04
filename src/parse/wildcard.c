/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/05 00:13:22 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_checkglobmatch(t_globs *globs, char *dir)
{	// should check if it actually matches with parent and sub dir
	globs->matches = ft_vastrjoin(4, globs->matches, dir, globs->subdir, " ");
}

void	ft_parsewildcard(t_cmds cmd, t_globs *globs)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	int				i;
	int				j;

	curdir = ft_getpwd(cmd.envp, 1);
	dir = opendir(curdir); // needs to run for every sub directory.
	while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
	{
		if (!ft_strncmp(dirents->d_name, globs->gstart, ft_strlen(globs->gstart))) // if start of glob matches
		{
			i = ft_strlen(globs->gend);
			j = ft_strlen(dirents->d_name);
			while (i && j && globs->gend[i] == dirents->d_name[j]) //while characters match from the end
			{
				i--;
				j--;
			}
			if (i == 0 && globs->gend[i] == dirents->d_name[j])// if first character of glob end matches
			{
				if (globs->period == 1)
					if (dirents->d_name[0] == '.')
						ft_checkglobmatch(globs, dirents->d_name);
				if (globs->period == 0)
					if (dirents->d_name[0] != '.')
						ft_checkglobmatch(globs, dirents->d_name);
			}
		}
	}
	if (!globs->matches)
	{
		globs->matches = ft_vastrjoin(4, globs->gstart, "*", globs->gend);
	}
	ft_printglobs(*globs, "end of parsewildcard");
}
