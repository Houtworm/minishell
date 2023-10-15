/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   alias.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:19 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/15 05:10:46 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printalias(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
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
	while (shell->alias[i].var)
	{
		if (!ft_strncmp(var, shell->alias[i].var, 100))
		{
			free(shell->alias[i].var);
			shell->alias[i].var = ft_strdup(val);
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

int	ft_alias(t_cmds cmd, t_shell *shell)
{
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd.arguments[1])
	{
		ft_printalias(shell);
		return (0);	
	}
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	while (cmd.arguments[1][i] != '\0' && cmd.arguments[1][i] != '=')
	{
		var[i] = cmd.arguments[1][i];
		i++;
	}
	if (cmd.arguments[1][i] != '=')
	{
		free(var);
		free(val);
		return (ft_moderrorreturn("not found", "alias", cmd.arguments[1], 1));
	}
	while (cmd.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arguments[1][1 + j + i];
		j++;
	}
	ft_addalias(shell, var, val);
	free(var);
	free(val);
	return (0);
}
