/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 03:56:16 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:15 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_setenv(char **envp, char *var, char *val)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
		{
			free(envp[i]);
			envp[i] = ft_calloc(1000, 8);
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
		i--;
		free(envp[i]);
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
		envp[i + 1] = NULL;
	}
	return (envp);
}

char	**ft_fdtocharpp(t_shell *msh)
{
	char	*line;
	char	**ret;
	int		i;
	int		status;
	int		fd;

	line = ft_strjoin(msh->tmpdir, "envpfile.tmp");
	fd = open(line, O_RDONLY);
	free(line);
	i = 0;
	ret = ft_calloc(10000, 8);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ret[i] = ft_strdup(line);
		free(line);
		status = get_next_line(fd, &line);
		i++;
	}
	free(line);
	ret[i] = NULL;
	close(fd);
	return (ret);
}

void	ft_charpptofd(char **array, t_shell *msh)
{
	int 	i;
	char	*temp;
	int		fd;

	temp = ft_strjoin(msh->tmpdir, "envpfile.tmp");
	fd = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(temp);
	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
	close(fd);
}
