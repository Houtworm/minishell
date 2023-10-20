/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/26 03:56:16 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/20 17:20:56 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_replaceenv(char **envp, char *var, char *val, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	free(envp[i]);
	envp[i] = ft_calloc(1000, 8);
	while (var[j])
	{
		envp[i][j] = var[j];
		j++;
	}
	envp[i][j] = '=';
	j++;
	while (val[k])
	{
		envp[i][j] = val[k];
		j++;
		k++;
	}
	envp[i][j] = '\0';
	return (envp);
}

char	**ft_newenv(char **envp, char *var, char *val, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	free(envp[i]);
	envp[i] = ft_calloc(8 * 512, 1);
	while (var[j] != '\0')
	{
		envp[i][j] = var[j];
		j++;
	}
	envp[i][j] = '=';
	j++;
	while (val[k] != '\0')
	{
		envp[i][k + j] = val[k];
		k++;
	}
	envp[i + 1] = NULL;
	return (envp);
}

char	**ft_setenv(char **envp, char *var, char *val)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
		{
			envp = ft_replaceenv(envp, var, val, i);
			return (envp);
		}
		i++;
	}
	envp = ft_newenv(envp, var, val, i - 1);
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
	int		i;
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
