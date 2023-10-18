/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 03:23:02 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:06 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parsealiases(t_commands *cmd, t_shell msh)
{
	int		i;
	char	*temp;
	int		varlen;

	i = 0;
	while (msh.alias[i].var)
	{
		varlen = ft_strlen(msh.alias[i].var);
		if (!ft_strncmp(msh.alias[i].var, cmd->line, varlen))
		{
			if (cmd->line[varlen] == ' ' || cmd->line[varlen] == '\0')
			{
				temp = ft_strjoin(msh.alias[i].val, &cmd->line[varlen]);
				free(cmd->line);
				cmd->line = ft_strdup(temp);
				free(temp);
			}
		}
		i++;
	}
}
