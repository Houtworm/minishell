/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   inputfile.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/17 16:21:59 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 23:22:04 by houtworm     \___)=(___/                 */
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

void	ft_heredocinit(int i, t_shell *msh, int forknumber, int icmd, char *start)
{
	int		j;
	char	*delimiter;
	char	*cmdn;
	char	*frkn;
	char	*end;
	char	*tmp;

	delimiter = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	end = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	i = i + 2;
	while (msh->frk[forknumber].cmd[icmd].line[i] == ' ')
		i++;
	j = 0;
	while (msh->frk[forknumber].cmd[icmd].line[i] && msh->frk[forknumber].cmd[icmd].line[i] != ' ')
	{
		delimiter[j] = msh->frk[forknumber].cmd[icmd].line[i];
		i++;
		j++;
	}
	delimiter[j] = '\0';
	j = 0;
	while (msh->frk[forknumber].cmd[icmd].line[i] == ' ')
		i++;
	frkn = ft_itoa(forknumber);
	cmdn = ft_itoa(icmd);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	free(frkn);
	free(cmdn);
	ft_heredoc(delimiter, tmp, *msh, msh->frk[forknumber].cmd[icmd].infiles);
	msh->frk[forknumber].cmd[icmd].infiles++;
	free(tmp);
	free(delimiter);
	while (msh->frk[forknumber].cmd[icmd].line[i])
	{
		end[j] = msh->frk[forknumber].cmd[icmd].line[i];
		i++;
		j++;
	}
	end[j] = '\0';
	free (msh->frk[forknumber].cmd[icmd].line);
	msh->frk[forknumber].cmd[icmd].line = ft_strjoin(start, end);
}

int	ft_infileinit(int i, t_shell *msh, int forknumber, int icmd, char *start)
{
	int		j;
	/*char	*delimiter;*/
	char	*cmdn;
	char	*frkn;
	char	*end;
	char	*tmp;
	char	quote;
	char	*file;

	i++;
	file = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	end = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	while (msh->frk[forknumber].cmd[icmd].line[i] && msh->frk[forknumber].cmd[icmd].line[i] == ' ')
		i++;
	j = 0;
	while (msh->frk[forknumber].cmd[icmd].line[i] && msh->frk[forknumber].cmd[icmd].line[i] != ' ' && msh->frk[forknumber].cmd[icmd].line[i] != '<')
	{
		if (msh->frk[forknumber].cmd[icmd].line[i] == '\'' || msh->frk[forknumber].cmd[icmd].line[i] == '\"')
		{
			quote = msh->frk[forknumber].cmd[icmd].line[i];
			i++;
			while (msh->frk[forknumber].cmd[icmd].line[i] != quote)
			{
				file[j] = msh->frk[forknumber].cmd[icmd].line[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			file[j] = msh->frk[forknumber].cmd[icmd].line[i];
			i++;
			j++;
		}
	}
	file[j] = '\0';
	file = ft_parsetilde(file, *msh);
	if (ft_checkinputfile(file))
	{
		free(file);
		return (2);
	}
	j = 0;
	while (msh->frk[forknumber].cmd[icmd].line[i] == ' ')
		i++;
	frkn = ft_itoa(forknumber);
	cmdn = ft_itoa(icmd);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	free(frkn);
	free(cmdn);
	ft_inputtofd(file, tmp, msh->frk[forknumber].cmd[icmd].infiles);
	free(tmp);
	msh->frk[forknumber].cmd[icmd].infiles++;
	while (msh->frk[forknumber].cmd[icmd].line[i])
	{
		end[j] = msh->frk[forknumber].cmd[icmd].line[i];
		i++;
		j++;
	}
	end[j] = '\0';
	free (msh->frk[forknumber].cmd[icmd].line);
	msh->frk[forknumber].cmd[icmd].line = ft_strjoin(start, end);
	free(file);
	return (0);
}

int	ft_getpos(t_shell *msh, int frkn, int icmd)
{
	int		i;
	char	quote;

	i = 0;
	while (msh->frk[frkn].cmd[icmd].line[i])
	{
		if (ft_strchr("\'\"", msh->frk[frkn].cmd[icmd].line[i]))
		{
			quote = msh->frk[frkn].cmd[icmd].line[i];
			i++;
			while (msh->frk[frkn].cmd[icmd].line[i] && msh->frk[frkn].cmd[icmd].line[i] != quote)
				i++;
			i++;
		}
		else if (msh->frk[frkn].cmd[icmd].line[i] == '<')
			break ;
		else
			i++;
	}
	return (i);
}

char	*ft_getstart(t_shell *msh, int frkn, int icmd)
{
	int		i;
	char	*start;
	char	quote;

	i = 0;
	start = ft_calloc(ft_strlen(msh->frk[frkn].cmd[icmd].line), 8);
	while (msh->frk[frkn].cmd[icmd].line[i])
	{
		if (ft_strchr("\'\"", msh->frk[frkn].cmd[icmd].line[i]))
		{
			quote = msh->frk[frkn].cmd[icmd].line[i];
			start[i] = msh->frk[frkn].cmd[icmd].line[i];
			i++;
			while (msh->frk[frkn].cmd[icmd].line[i] && msh->frk[frkn].cmd[icmd].line[i] != quote)
			{
				start[i] = msh->frk[frkn].cmd[icmd].line[i];
				i++;
			}
			start[i] = msh->frk[frkn].cmd[icmd].line[i];
			i++;
		}
		else if (msh->frk[frkn].cmd[icmd].line[i] == '<')
		{
			break ;
		}
		else
		{
			start[i] = msh->frk[frkn].cmd[icmd].line[i];
			i++;
		}
	}
	start[i] = '\0';
	return (start);
}

int ft_parseinputfiles(t_shell *msh, int frkn)
{
	int		icmd;
	int		i;
	/*int		j;*/
	char	quote;
	/*char	*tmp;*/
	char	*start;
	/*char	*end;*/
	/*char	*delimiter;*/
	/*char	*frkn;*/
	/*char	*cmdn;*/
	char	*file;

	icmd = 0;
	while (icmd < msh->frk[frkn].cmdamount)
	{
		msh->frk[frkn].cmd[icmd].infiles = 0;
		if (ft_checkoutquote(msh->frk[frkn].cmd[icmd].line, '<', 2) >= 0)
		{
			start = ft_calloc(ft_strlen(msh->frk[frkn].cmd[icmd].line), 8);
			file = ft_calloc(ft_strlen(msh->frk[frkn].cmd[icmd].line), 8);
			i = 0;
			while (msh->frk[frkn].cmd[icmd].line[i])
			{
				if (ft_strchr("\'\"", msh->frk[frkn].cmd[icmd].line[i]))
				{
					quote = msh->frk[frkn].cmd[icmd].line[i];
					start[i] = msh->frk[frkn].cmd[icmd].line[i];
					i++;
					while (msh->frk[frkn].cmd[icmd].line[i] && msh->frk[frkn].cmd[icmd].line[i] != quote)
					{
						start[i] = msh->frk[frkn].cmd[icmd].line[i];
						i++;
					}
					start[i] = msh->frk[frkn].cmd[icmd].line[i];
					i++;
				}
				else if (msh->frk[frkn].cmd[icmd].line[i] == '<')
				{
					start[i] = '\0';
					if (msh->frk[frkn].cmd[icmd].line[i + 1] == '<')
						ft_heredocinit(i, msh, frkn, icmd, start);
					else
						if (ft_infileinit(i, msh, frkn, icmd, start))
							return (2);
					i = 0;
				}
				else
				{
					start[i] = msh->frk[frkn].cmd[icmd].line[i];
					i++;
				}
			}
			free(start);
			free(file);
		}
		icmd++;
	}
	return (0);
}
