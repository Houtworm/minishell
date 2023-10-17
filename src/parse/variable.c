/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/17 15:17:59 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	ft_parsevariable(t_shell *msh, int frkn)*/
/*{*/
	/*int		i;*/
	/*int		j;*/
	/*char	*begin;*/
	/*char	*var;*/
	/*char	*val;*/
	/*char	*rest;*/

	/*begin = ft_calloc((ft_strlen(msh->frk[frkn].pipeline) + 1) * 8, 1);*/
	/*var = ft_calloc((ft_strlen(msh->frk[frkn].pipeline) + 1) * 8, 1);*/
	/*rest = ft_calloc((ft_strlen(msh->frk[frkn].pipeline) + 1) * 8, 1);*/
	/*while (ft_checkoutquotevar(msh->frk[frkn].pipeline) >= 0)*/
	/*{*/
		/*i = 0;*/
		/*j = 0;*/
		/*while (msh->frk[frkn].pipeline[i] && msh->frk[frkn].pipeline[i] != '$')*/
		/*{*/
			/*if (msh->frk[frkn].pipeline[i] == '\'')*/
			/*{*/
				/*begin[j] = msh->frk[frkn].pipeline[i];*/
				/*i++;*/
				/*j++;*/
				/*while (msh->frk[frkn].pipeline[i] && msh->frk[frkn].pipeline[i] != '\'')*/
				/*{*/
					/*begin[j] = msh->frk[frkn].pipeline[i];*/
					/*i++;*/
					/*j++;*/
				/*}*/
			/*}*/
			/*if (msh->frk[frkn].pipeline[i] == '\"')*/
			/*{*/
				/*begin[j] = msh->frk[frkn].pipeline[i];*/
				/*i++;*/
				/*j++;*/
				/*while (msh->frk[frkn].pipeline[i] && msh->frk[frkn].pipeline[i] != '\"')*/
				/*{*/
					/*if (msh->frk[frkn].pipeline[i] == '$' && msh->frk[frkn].pipeline[i + 1] != '\'' && msh->frk[frkn].pipeline[i + 1] != '\"' && msh->frk[frkn].pipeline[i + 1] != '(')*/
						/*break ;*/
					/*begin[j] = msh->frk[frkn].pipeline[i];*/
					/*i++;*/
					/*j++;*/
				/*}*/
			/*}*/
			/*if (!msh->frk[frkn].pipeline[i] || (msh->frk[frkn].pipeline[i] == '$' && msh->frk[frkn].pipeline[i + 1] != '\'' && msh->frk[frkn].pipeline[i + 1] != '\"' && msh->frk[frkn].pipeline[i + 1] != '('))*/
				/*break ;*/
			/*begin[j] = msh->frk[frkn].pipeline[i];*/
			/*i++;*/
			/*j++;*/
			/*if (msh->frk[frkn].pipeline[i] == '$' && msh->frk[frkn].pipeline[i + 1] == '(')*/
			/*{*/
				/*while (msh->frk[frkn].pipeline[i] != ')')*/
				/*{*/
					/*begin[j] = msh->frk[frkn].pipeline[i];*/
					/*j++;*/
					/*i++;*/
				/*}*/
				/*begin[j] = msh->frk[frkn].pipeline[i];*/
				/*i++;*/
				/*j++;*/
			/*}*/
		/*}*/
		/*if (msh->frk[frkn].pipeline[i] == '$')*/
		/*{*/
			/*begin[j] = '\0';*/
			/*i++;*/
		/*}*/
		/*if (msh->frk[frkn].pipeline[i] == '?')*/
		/*{*/
			/*val = ft_itoa(msh->code % 256);*/
			/*i++;*/
		/*}*/
		/*else if (msh->frk[frkn].pipeline[i] == '$')*/
		/*{*/
			/*val = ft_itoa(msh->pid);*/
			/*i++;*/
		/*}*/
		/*else if (msh->frk[frkn].pipeline[i] == ' ')*/
		/*{*/
			/*val = ft_strdup("$");*/
			/*i++;*/
		/*}*/
		/*else if (!msh->frk[frkn].pipeline[i])*/
			/*val = ft_strdup("$");*/
		/*else*/
		/*{*/
			/*j = 0;*/
			/*while ((msh->frk[frkn].pipeline[i] >= 'A' && msh->frk[frkn].pipeline[i] <= 'Z') || (msh->frk[frkn].pipeline[i] >= 'a' && msh->frk[frkn].pipeline[i] <= 'z' ) || msh->frk[frkn].pipeline[i] == '_')*/
			/*{*/
				/*var[j] = msh->frk[frkn].pipeline[i];*/
				/*i++;*/
				/*j++;*/
			/*}*/
			/*var[j] = '\0';*/
			/*val = ft_getenvval(msh->envp, var);*/
		/*}*/
		/*j = 0;*/
		/*while (msh->frk[frkn].pipeline[i])*/
		/*{*/
			/*rest[j] = msh->frk[frkn].pipeline[i];*/
			/*i++;*/
			/*j++;*/
		/*}*/
		/*rest[j] = '\0';*/
		/*free (msh->frk[frkn].pipeline);*/
		/*msh->frk[frkn].pipeline = ft_vastrjoin(3, begin, val, rest);*/
		/*free (val);*/
	/*}*/
	/*ft_vafree(3, begin, var, rest);*/
	/*return (0);*/
/*}*/

int	ft_parsevariable(t_commands *cmd, t_shell msh)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	while (ft_checkoutquotevar(cmd->pipeline) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '$')
		{
			if (cmd->pipeline[i] == '\'')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\'')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			if (cmd->pipeline[i] == '\"')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\"')
				{
					if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] != '\'' && cmd->pipeline[i + 1] != '\"' && cmd->pipeline[i + 1] != '(')
						break ;
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			if (!cmd->pipeline[i] || (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] != '\'' && cmd->pipeline[i + 1] != '\"' && cmd->pipeline[i + 1] != '('))
				break ;
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
			if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] == '(')
			{
				while (cmd->pipeline[i] != ')')
				{
					begin[j] = cmd->pipeline[i];
					j++;
					i++;
				}
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
			}
		}
		if (cmd->pipeline[i] == '$')
		{
			begin[j] = '\0';
			i++;
		}
		if (cmd->pipeline[i] == '?')
		{
			val = ft_itoa(msh.code % 256);
			i++;
		}
		else if (cmd->pipeline[i] == '$')
		{
			val = ft_itoa(msh.pid);
			i++;
		}
		else if (cmd->pipeline[i] == ' ')
		{
			val = ft_strdup("$");
			i++;
		}
		else if (!cmd->pipeline[i])
			val = ft_strdup("$");
		else
		{
			j = 0;
			while ((cmd->pipeline[i] >= 'A' && cmd->pipeline[i] <= 'Z') || (cmd->pipeline[i] >= 'a' && cmd->pipeline[i] <= 'z' ) || cmd->pipeline[i] == '_')
			{
				var[j] = cmd->pipeline[i];
				i++;
				j++;
			}
			var[j] = '\0';
			val = ft_getenvval(msh.envp, var);
		}
		j = 0;
		while (cmd->pipeline[i])
		{
			rest[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		rest[j] = '\0';
		free (cmd->pipeline);
		cmd->pipeline = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (0);
}
