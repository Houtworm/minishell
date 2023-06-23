/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   chdir.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 17:21:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/06/23 18:58:29 by houtworm     \___)=(___/                 */
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
		char	**temp;

		temp = ft_calloc((i + 2) * 512, 1);
		/*temp = envp;*/
		j = 0;
		while (var[j])
		{
			/*temp[i][j] = var[j];*/
			j++;
		}
		printf("blabla\n");
		/*temp[i][j] = '=';*/
		j++;
		k = 0;
		while (val[k])
		{
			/*temp[i][k + j] = val[k];*/
			k++;
		}
		/*temp[i][j] = '\0';*/
		/*temp[i + 1][0] = '\0';*/
		/*ft_frearr(envp);*/
		/*envp = ft_calloc((i + 2) * 512, 1);*/
		/*envp = temp;*/
		/*ft_frearr(temp);*/
	}
	return (0);
}

int	ft_chdir(t_shell *strct)
{
	char	*line;
	char	*dir;
	int		i;
	char	*cwd;

	cwd = malloc(512);
	getcwd(cwd, 512);
	i = 0;
	dir = ft_calloc(512, 1);
	line = strct->line;
	while (line[i + 2] != '\0')
	{
		while (line[i + 3] == ' ')
			i++;
		dir[i] = line[i + 3];
		i++;
	}
	if (!ft_strncmp(dir,  "~\0", 2) || i == 0)
	{
		dir = ft_gethome(strct->envp);
	}
	if (!ft_strncmp(dir,  "-\0", 2))
	{
		dir = ft_getenvval(strct->envp, "OLDPWD");
	}
	if (chdir(dir))
	{
		free(dir);
		free(cwd);
		return (1);
	}
	ft_setenv(strct->envp, "OLDPWD", cwd);
	getcwd(cwd, 512);
	ft_setenv(strct->envp, "PWD", cwd);
	free(dir);
	free(cwd);
	return (0);
}
