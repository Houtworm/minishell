/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/24 15:27:22 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_procwildcards(t_shell *strct)
{

	strct++;
}

void	ft_procsquarebrack(t_shell *strct)
{
	char	*line;
	int		i;
	int		options[256];

	i = 0;
	line = strct->line;
	while (*line)
	{
		// somehow save characters before [
		while (*line && *line != '[')
			line++;
		line++;
		while (*line && *line != ']')
		{
			options[i] = (int)*line;
			i++;
		}
		i = options[0];
		/*if (*line)*/
			//  options and expand to the files that match
	}
}

int	ft_chrstrexquo(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
				s++;
		}
		if (*s == '\"')
		{
			s++;
			while (*s != '\"')
				s++;
		}
		s++;
	}
	if (c == *s)
		return (1);
	return (0);
}

void	ft_expandcommands(t_shell *strct)
{
	/*int		i;*/

	/*i = 0;*/
	if (ft_chrstrexquo('[', strct->line))
	{
		ft_procsquarebrack(strct);
	}
	/*if (ft_chrstrexquo('?', strct->line))*/
	/*{*/
		/*ft_procquestionmark(strct);*/
	/*}*/
	/*if (ft_chrstrexquo('*', strct->line))*/
	/*{*/
		/*ft_procwildcard(strct);*/
	/*}*/
	/*if (ft_chrstrexquo('`', strct->line))*/
	/*{*/
		/*ft_proccmdsubst(strct);*/
	/*}*/
}

int	*ft_parseline(char *line, t_shell *shell)
{

	shell->line = line;
	char	**paths;

	shell->arguments = ft_split(line, ' ');
	paths = ft_getpaths(shell->envp, 1);
	shell->absolute = ft_abspathcmd(paths, shell->arguments[0]);
	ft_frearr(paths);

/*yuka working
	char	**arr;

	if (!check_quote_closed(line))
		printf("num of str = %d\n", count_str(line, '|'));
	arr = split_not_quote(line, '|');
	ft_strct_per_cmd(arr, shell);
	printf("end of testing\n");
	exit(0);
//*/
	return (SUCCESS);
}
