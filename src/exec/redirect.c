/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   redirect.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/17 19:54:30 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 21:13:19 by houtworm     \___)=(___/                 */
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

void	ft_redirectoutput(char **outfile, int *append, int forknbr, t_shell *msh)
{
	char	*outtmp;
	char	*line;
	int		i;

	line = ft_itoa(forknbr);
	outtmp = ft_vastrjoin(4, msh->tmpdir, "outputfile", line, ".tmp");
	free(line);
	i = 0;
	while (outfile[i] && outfile[i + 1]) //comment out these lines for zsh behavior
		i++; //comment out these lines for zsh behavior
	while (outfile[i])
	{
		ft_redirecttofile(outfile, append, outtmp, i);
		i++;
	}
	free(outtmp);
}
