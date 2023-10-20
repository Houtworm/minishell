/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputfile2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 02:37:58 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 17:42:24 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

	// add below lines to enable zsh behavior
	/*if (inputnumber)*/
		/*tempfd = open(tmpfile, O_RDWR | O_CREAT | O_APPEND, 0666);*/
	/*else*/

int	ft_inputtofd(char *infile, char *tmpfile, int inputnumber)
{
	int		fdi;
	char	*line;
	int		tempfd;

	inputnumber = inputnumber;
	tempfd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	fdi = open(infile, O_RDONLY);
	while (get_next_line(fdi, &line) > 0)
	{
		if (!line)
			ft_errorexit("Error allocating memory", "ft_heredoc", 1);
		ft_putendl_fd(line, tempfd);
		free(line);
	}
	free(line);
	close(fdi);
	close(tempfd);
	return (fdi);
}

char	*ft_getendinputfile(t_shell *msh, int forknumber, int icmd, int i)
{
	char	*end;
	int		j;

	j = 0;
	end = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	while (msh->frk[forknumber].cmd[icmd].line[i])
	{
		end[j] = msh->frk[forknumber].cmd[icmd].line[i];
		i++;
		j++;
	}
	end[j] = '\0';
	return (end);
}

void	ft_writefiletoinput(t_shell *msh, int frki, int icmd, char *file)
{
	char	*cmdn;
	char	*frkn;
	char	*tmp;

	frkn = ft_itoa(frki);
	cmdn = ft_itoa(icmd);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	ft_inputtofd(file, tmp, msh->frk[frki].cmd[icmd].infiles);
	ft_vafree(3, frkn, cmdn, tmp);
	msh->frk[frki].cmd[icmd].infiles++;
}

char	*ft_getfileinputfile(t_shell *msh, int f, int c, int i)
{
	char	*file;
	int		j;

	j = 0;
	file = ft_calloc(ft_strlen(msh->frk[f].cmd[c].line), 8);
	while (!ft_strchr(" <", msh->frk[f].cmd[c].line[i]))
		file = ft_cpnonquote(msh->frk[f].cmd[c].line, file, &i, &j);
	file[j] = '\0';
	return (file);
}

int	ft_getfilepos(t_shell *msh, int f, int c, int i)
{
	char	quote;

	while (!ft_strchr(" <", msh->frk[f].cmd[c].line[i]))
	{
		if (ft_strchr("'\'\"", msh->frk[f].cmd[c].line[i]))
		{
			quote = msh->frk[f].cmd[c].line[i];
			i++;
			while (msh->frk[f].cmd[c].line[i] != quote)
			{
				i++;
			}
			i++;
		}
		else
		{
			i++;
		}
	}
	return (i);
}
