/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:06:19 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:29 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printalias(t_shell *msh, t_commands cmd, int mode)
{
	int		i;
	char	*str;

	i = 0;
	if (mode)
	{
		while (msh->alias[i].var)
		{
			if (!ft_strncmp(cmd.arg[1], msh->alias[i].var, 100))
				if (printf("%s=%s\n", msh->alias[i].var, msh->alias[i].val))
					return (0);
			i++;
		}
		return (ft_errorret2("not found", "alias", cmd.arg[1], 1));
	}
	while (msh->alias[i].var)
	{
		str = ft_vastrjoin(3, msh->alias[i].var, "=", msh->alias[i].val);
		ft_putendl(str);
		free(str);
		i++;
	}
	return (0);
}

int	ft_addalias(t_shell *msh, char *var, char *val)
{
	int		i;

	i = 0;
	while (msh->alias[i].var)
	{
		if (!ft_strncmp(var, msh->alias[i].var, 100))
		{
			free(msh->alias[i].val);
			msh->alias[i].val = ft_strdup(val);
			return (0);
		}
		i++;
	}
	if (!msh->alias[i].var)
	{
		msh->alias[i].var = ft_strdup(var);
		msh->alias[i].val = ft_strdup(val);
	}
	return (0);
}

char	*ft_getvaralias(t_commands cmd)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_calloc(512, 1);
	while (cmd.arg[1][i] != '\0' && cmd.arg[1][i] != '=')
	{
		var[i] = cmd.arg[1][i];
		i++;
	}
	var[i] = '\0';
	if (cmd.arg[1][i] != '=')
	{
		free(var);
		return (NULL);
	}
	return (var);
}

char	*ft_getvalalias(t_commands cmd, int i)
{
	char	*val;
	int		j;

	j = 0;
	val = ft_calloc(512, 1);
	while (cmd.arg[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arg[1][1 + j + i];
		j++;
	}
	val[j] = '\0';
	return (val);
}

int	ft_alias(t_commands cmd, t_shell *msh)
{
	char	*var;
	char	*val;

	if (!cmd.arg[1])
		return (ft_printalias(msh, cmd, 0));
	var = ft_getvaralias(cmd);
	if (var == NULL)
		return (ft_printalias(msh, cmd, 1));
	val = ft_getvalalias(cmd, ft_strlen(var));
	ft_addalias(msh, var, val);
	free(var);
	free(val);
	return (0);
}
