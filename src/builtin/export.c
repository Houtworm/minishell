/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:12:44 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/19 04:51:14 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printexport(t_shell *m)
{
	int		i;
	int		j;
	char	*s;
	char	*t;

	i = 0;
	t = ft_calloc(1000, 8);
	while (m->envp[i])
	{
		j = 0;
		while (m->envp[i][j] && m->envp[i][j] != '=')
		{
			t[j] = m->envp[i][j];
			j++;
		}
		t[j] = '\0';
		s = ft_vastrjoin(5, "declare -x ", t, "=\"", &m->envp[i][j + 1], "\"");
		ft_putendl(s);
		free(s);
		i++;
	}
	free(t);
	return (0);
}

int	ft_export(t_commands cmd, t_shell *msh)
{
	char	**envp;
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd.arg[1])
		return (ft_printexport(msh));
	if (cmd.arg[1][0] == '-')
		return (ft_errorret("invalid option", "export", 2));
	if (!ft_isalpha(cmd.arg[1][i]) || cmd.arg[1][i] != '_')
		return (ft_errorret2("not a valid identifier", cmd.arg[1], "export", 1));
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	while (cmd.arg[1][i] != '\0' && cmd.arg[1][i] != '=')
	{
		if (!ft_isalnum(cmd.arg[1][i]) && cmd.arg[1][i] != '_')
		{
			ft_vafree(2, var, val);
			return (ft_errorret2("not a valid identifier", cmd.arg[1], "export", 1));
		}
		var[i] = cmd.arg[1][i];
		i++;
	}
	if (!i || (cmd.arg[2] && cmd.arg[2][0] == '='))
	{
		ft_vafree(2, var, val);
		return (ft_errorret("not a valid identifier", "export", 1));
	}
	while (cmd.arg[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arg[1][1 + j + i];
		j++;
	}
	envp = ft_setenv(msh->envp, var, val);
	ft_charpptofd(envp, msh);
	ft_vafree(2, var, val);
	return (0);
}
