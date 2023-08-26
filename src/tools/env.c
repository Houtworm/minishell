/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   env.c                                           |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/26 03:56:16 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 07:34:37 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_setenv(char **envp, char *var, char *val)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = ft_strlen(var);
	tmp = ft_calloc(i + 2, 1);
	tmp[i + 1] = '=';
	tmp[i + 2] = '\0';
	while (i >= 0)
	{
		tmp[i] = var[i];
		i--;
	}
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
		{
			j = 0;
			while (var[j])
			{
				envp[i][j] = var[j];
				j++;
			}
			envp[i][j] = '=';
			j++;
			k = 0;
			while (val[k])
			{
				envp[i][j] = val[k];
				j++;
				k++;
			}
			envp[i][j] = '\0';
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		envp[i] = ft_calloc(8 * 512, 1);
		j = 0;
		while (var[j] != '\0')
		{
			envp[i][j] = var[j];
			j++;
		}
		envp[i][j] = '=';
		j++;
		k = 0;
		while (val[k] != '\0')
		{
			envp[i][k + j] = val[k];
			k++;
		}
		envp[i + 1] = ft_calloc(8 * 2, 1);
	}
	return (0);
}

char	**ft_fdtocharpp(int	fd)
{
	char	*line;
	char	**ret;
	int		i;
	int		status;

	i = 0;
	ret = ft_calloc(sizeof(ret) * 1024, 1);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ret[i] = ft_strdup(line);
		free(line);
		status = get_next_line(fd, &line);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_charpptofd(char **array, int fd)
{
	int i;

	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
}
