/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   inputfile2.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/18 02:37:58 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/18 02:38:09 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_inputtofd(char *infile, char *tmpfile, int inputnumber)
{
	int		fdi;
	char	*line;
	int		ret;
	int		tempfd;

	inputnumber = inputnumber;
	/*if (inputnumber) // comment this line for bash behavior*/
		/*tempfd = open(tmpfile, O_RDWR | O_CREAT | O_APPEND, 0666); // comment this line for bash behavior*/
	/*else // comment this line for bash behavior*/
		tempfd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	fdi = open(infile, O_RDONLY);
	while ((ret = get_next_line(fdi, &line)) > 0)
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
	free(frkn);
	free(cmdn);
	ft_inputtofd(file, tmp, msh->frk[frki].cmd[icmd].infiles);
	free(tmp);
	msh->frk[frki].cmd[icmd].infiles++;
}

char	*ft_getfileinputfile(t_shell *msh, int f, int c, int i)
{
	char	quote;
	int		j;
	char	*file;

	j = 0;
	file = ft_calloc(ft_strlen(msh->frk[f].cmd[c].line), 8);
	while (!ft_strchr(" <", msh->frk[f].cmd[c].line[i + j]))
	{
		if (ft_strchr("\'\"", msh->frk[f].cmd[c].line[i + j]))
		{
			quote = msh->frk[f].cmd[c].line[i + j];
			i++;
			while (msh->frk[f].cmd[c].line[i + j] != quote)
				if ((file[j] = msh->frk[f].cmd[c].line[i + j]))
					j++;
			i++;
		}
		else
			if ((file[j] = msh->frk[f].cmd[c].line[i + j]))
				j++;
	}
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
