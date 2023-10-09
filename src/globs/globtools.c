/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globtools.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:34:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/09 05:38:26 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	ft_cleanglob(t_globs *globs)*/
/*{*/
	

/*}*/

void	ft_backupglob(t_globs *globs)
{
  	char	*temp;

	if (globs->subdir[0])
	{
		temp = ft_cpptostr(globs->subdir);
		globs->backup = ft_vastrjoin(5, globs->pardir, globs->gstart, globs->glob, globs->gend, temp); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
		free(temp);
	}
	else
		globs->backup = ft_vastrjoin(4, globs->pardir, globs->gstart, globs->glob, globs->gend); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
}

void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match); // add the match
	/*printf("ft_addglobmatch added %s as a match\n", match);*/
	globs->matchcount++;
}

int	ft_newpipeline(t_globs *globs)
{ // simply parses the results into the new pipeline
	int		i;
	int		j;
	int		k;
	char	*temp;

	if (!globs->matches[0])
	{
		/*printf("ft_parseglob no matches found\n");*/
		temp = ft_strdup(globs->backup); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
		globs->linecount = globs->linecount + ft_strlen(temp);
	}
	else
	{
		temp = ft_calloc(100000, 8);
		k = 0;
		i = 0;
		while (globs->matches[i])
		{
			j = 0;
			if (ft_isallbyte(globs->matches[i], ' '))
			{
				temp[k] = '\'';
				k++;
			}
			while (globs->matches[i][j])
			{
				temp[k] = globs->matches[i][j];
				j++;
				k++;
			}
			if (ft_isallbyte(globs->matches[i], ' '))
			{
				temp[k] = '\'';
				k++;
			}
			temp[k] = ' ';
			k++;
			i++;
		}
		temp[k] = '\0';
		ft_frearr(globs->matches);
		free(globs->pipeline);
		globs->pipeline = ft_vastrjoin(3, globs->start, temp, globs->end); // new pipeline
		globs->linecount = globs->linecount + k; // new linecount
		globs->matches = ft_calloc(100, 4096);
		globs->matchcount = 0;
	}
	free(temp);
	return (0);
}
