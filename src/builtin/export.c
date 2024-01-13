/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:12:44 by houtworm      #+#    #+#                 */
/*   Updated: 2024/01/13 07:58:49 by houtworm      ########   odam.nl         */
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

int	ft_setexport(t_shell *msh, t_commands c, char *var, char *val)
{
	int		i;
	int		j;
	char	**envp;

	i = 0;
	j = 0;
	while (c.arg[1][i] != '\0' && c.arg[1][i] != '=')
	{
		if (!ft_isalnum(c.arg[1][i]) && c.arg[1][i] != '_')
			return (ft_errorret("not a valid identifier", "export", 1));
		var[i] = c.arg[1][i];
		i++;
	}
	if (!i || (c.arg[2] && c.arg[2][0] == '='))
		return (ft_errorret("not a valid identifier", "export", 1));
	while (c.arg[1][i + j + 1] != '\0')
	{
		val[j] = c.arg[1][1 + j + i];
		j++;
	}
	envp = ft_setenv(msh->envp, var, val);
	ft_charpptofd(envp, msh);
	return (0);
}

int	ft_export(t_commands c, t_shell *msh)
{
	char	*var;
	char	*val;
	int		ret;

	if (!c.arg[1])
		return (ft_printexport(msh));
	if (c.arg[1][0] == '-')
		return (ft_errorret("invalid option", "export", 2));
	if (!ft_isalpha(c.arg[1][0]) && c.arg[1][0] != '_')
		return (ft_errorret2("not a valid identifier", c.arg[1], "export", 1));
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	ret = ft_setexport(msh, c, var, val);
	ft_vafree(2, var, val);
	return (ret);
}
