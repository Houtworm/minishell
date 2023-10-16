/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   alias.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:19 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 08:38:25 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printalias(t_shell *shell, t_cmds cmd, int mode)
{
	int		i;
	char	*str;

	i = 0;
	if (mode)
	{
		while (shell->alias[i].var)
		{
			if (!ft_strncmp(cmd.arguments[1], shell->alias[i].var, 100))
				if (printf("%s=%s\n", shell->alias[i].var, shell->alias[i].val))
					return (0);
			i++;
		}
		return (ft_moderrorreturn("not found", "alias", cmd.arguments[1], 1));
	}
	while (shell->alias[i].var)
	{
		str = ft_vastrjoin(3, shell->alias[i].var, "=", shell->alias[i].val);
		ft_putendl(str);
		free(str);
		i++;
	}
	return (0);
}

int	ft_addalias(t_shell *shell, char *var, char *val)
{
	int		i;

	i = 0;
	printf("var: %s\nval: %s\n", var, val);
	while (shell->alias[i].var)
	{
		printf("alias: %s\nnewar: %s\n", shell->alias[i].var, var);
		if (!ft_strncmp(var, shell->alias[i].var, 100))
		{
			free(shell->alias[i].val);
			shell->alias[i].val = ft_strdup(val);
			return (0);
		}
		i++;
	}
	if (!shell->alias[i].var)
	{
		shell->alias[i].var = ft_strdup(var);
		shell->alias[i].val = ft_strdup(val);
	}
	return (0);
}

char	*ft_getvaralias(t_cmds cmd)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_calloc(512, 1);
	while (cmd.arguments[1][i] != '\0' && cmd.arguments[1][i] != '=')
	{
		var[i] = cmd.arguments[1][i];
		i++;
	}
	var[i] = '\0';
	if (cmd.arguments[1][i] != '=')
	{
		free(var);
		return (NULL);
	}
	return (var);
}

char	*ft_getvalalias(t_cmds cmd, int i)
{
	char	*val;
	int		j;

	j = 0;
	val = ft_calloc(512, 1);
	while (cmd.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arguments[1][1 + j + i];
		j++;
	}
	val[j] = '\0';
	return (val);
}

int	ft_alias(t_cmds cmd, t_shell *shell)
{
	char	*var;
	char	*val;

	if (!cmd.arguments[1])
		return (ft_printalias(shell, cmd, 0));	
	var = ft_getvaralias(cmd);
	if (var == NULL)
		return (ft_printalias(shell, cmd, 1));	
	val = ft_getvalalias(cmd, ft_strlen(var));
	ft_addalias(shell, var, val);
	free(var);
	free(val);
	return (0);
}
