/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 19:54:30 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/23 19:16:09 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_redirecttofile(char **outfile, int *append, char *outtmp, int i)
{
	int		fdread;
	int		fdo;
	char	*line;
	int		ret;

	fdread = open(outtmp, O_RDONLY);
	if (append[i])
		fdo = open(outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fdo = open(outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fdread, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
		if (ret == 0)
			ft_putstr_fd(line, fdo);
		else
			ft_putendl_fd(line, fdo);
		free(line);
	}
	close (fdo);
	close(fdread);
}

void	ft_rediout(char **outfile, int *append, int frkn, t_shell *msh)
{
	char	*outtmp;
	char	*line;
	int		i;

	line = ft_itoa(frkn);
	outtmp = ft_vastrjoin(4, msh->tmpdir, "outputfile", line, ".tmp");
	free(line);
	i = 0;
	while (outfile[i] && outfile[i + 1])
		i++;
	while (outfile[i])
	{
		ft_redirecttofile(outfile, append, outtmp, i);
		i++;
	}
	free(outtmp);
}
