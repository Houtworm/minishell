/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exit.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 18:48:08 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 14:40:01 by djonker      \___)=(___/                 */
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
int	ft_checklonglong(char *str)
{
	unsigned long long 	number;
	unsigned long long 	compare;
	int					i;
	int					negative;

	compare = 9223372036854775807;
	i = 0;
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
	/*printf("%llu\n", number);*/
	if (negative == 1)
		if (number > compare)
			return (1);
	if (negative == -1)
		if (number > compare + 1)
			return (1);
	return (0);
}

int	ft_exit(t_cmds cmds, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmds.arguments[1])
		exit(0);
	if (cmds.arguments[1][0] == '\0')
		return (ft_moderrorreturn ("numeric argument required", "exit", cmds.arguments[1], 2));
	if (ft_checklonglong(cmds.arguments[1]))
		return (ft_errorreturn ("numeric argument required", "exit", 2));
	if (cmds.arguments[1][i] == '-')
		i++;
	while (cmds.arguments[1][i])
	{
		if (cmds.arguments[1][i] < '0' || cmds.arguments[1][i] > '9' )
		{
			ft_putendl_fd("exit", 2);
			return (ft_moderrorreturn ("numeric argument required", "exit", cmds.arguments[1], 2));
		}
		i++;
	}
		return (ft_atol(cmds.arguments[1]));
	return (0);
	shell = shell;
}
