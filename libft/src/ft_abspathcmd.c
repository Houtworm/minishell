/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_abspathcmd.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/20 16:39:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/09 07:03:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_abspathcmd(char **paths, char *cmd)
{
	char	*absolute;
	int		i;

	i = 0;
	if (!paths)
		return (cmd);
	if (cmd && ft_chrstr('/', cmd))
		absolute = ft_strdup(cmd);
	else
		absolute = ft_strjoin(paths[i], cmd);
	while (access(absolute, F_OK) && paths[i] && !ft_chrstr('/', cmd))
	{
		free(absolute);
		i++;
		absolute = ft_strjoin(paths[i], cmd);
	}
	return (absolute);
}
