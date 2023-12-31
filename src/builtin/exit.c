/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 18:48:08 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/27 13:23:21 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

unsigned long long	ft_atoull(char *str, int c)
{
	unsigned long long	r;

	r = 0;
	while (str[c] && (str[c] == 32 || (str[c] > 8 && str[c] < 14)))
		c++;
	while (str[c] >= '0' && str[c] <= '9')
	{
		r = 10 * r + (str[c] - '0');
		c++;
	}
	return (r);
}

int	ft_checklonglong(char *str, int i)
{
	unsigned long long	number;
	unsigned long long	compare;
	int					negative;

	compare = 9223372036854775807;
	negative = 1;
	while (str[i] && (str[i] == 32 || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '0')
		return (0);
	number = ft_atoull(str, 0);
	if (str[i] == '-')
	{
		i++;
		number = ft_atoull(str, i);
		negative = -1;
	}
	if (negative == 1)
		if (number > compare)
			return (1);
	if (negative == -1)
		if (number > compare + 1)
			return (1);
	return (0);
}

int	ft_exit(t_commands cmd, t_shell *msh)
{
	int	i;

	i = 0;
	msh->nothing = 1;
	if (!cmd.arg[1])
		return (0);
	if (cmd.arg[1][0] == '\0' || ft_checklonglong(cmd.arg[1], 0))
		return (ft_errorret("numeric argument required", "exit", 2));
	if (cmd.arg[1][i] == '-')
		i++;
	while (cmd.arg[1][i])
	{
		if (cmd.arg[1][i] < '0' || cmd.arg[1][i] > '9' )
		{
			ft_putendl_fd("exit", 2);
			ft_errorret2 ("numeric argument required", "exit", cmd.arg[1], 2);
			return (2);
		}
		i++;
	}
	return (ft_atol(cmd.arg[1]));
}
