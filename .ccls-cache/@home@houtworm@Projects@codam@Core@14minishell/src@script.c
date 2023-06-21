/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:20:31 by houtworm          #+#    #+#             */
/*   Updated: 2023/05/21 18:18:38 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_runscript(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		fd;
	char	*line;
	int		ret;
	int		i;

	i = 1;
	ret = 1;
	shell = ft_initstruct(envp);
	while (i < argc)
	{
		fd = open(argv[1], O_RDONLY);
		while (ret > 0)
		{
			ret = get_next_line(fd, &line); // write second GNL for \ at end of line
			ft_parseline(line, shell);
			ft_executecommands(shell);
			free(line);
		}
		i++;
	}
	// cleanup
	return (SUCCESS);
}
