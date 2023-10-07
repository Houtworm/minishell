/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globtools.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:34:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 06:44:26 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match); // add the match
	/*printf("ft_addglobmatch added %s as a match\n", match);*/
	globs->matchcount++;
}

int	ft_newpipeline(t_globs *globs)
{ // simply parses the results into the new pipeline
  	char	*temp;
  	char	*temp2;
	int		i;
	int		j;
	int		k;

	if (!globs->matches[0])
	{
		/*printf("ft_parseglob no matches found\n");*/
		if (globs->subdir[0])
		{
			temp2 = ft_cpptostr(globs->subdir);
			temp = ft_vastrjoin(5, globs->pardir, globs->gstart, globs->glob, globs->gend, temp2); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
			free(temp2);
		}
		else
			temp = ft_vastrjoin(4, globs->pardir, globs->gstart, globs->glob, globs->gend); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
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
			while (globs->matches[i][j])
			{
				temp[k] = globs->matches[i][j];
				j++;
				k++;
			}
			temp[k] = ' ';
			k++;
			i++;
		}
		/*ft_frearr(globs->matches);*/
		free(globs->pipeline);
		globs->pipeline = ft_vastrjoin(3, globs->start, temp, globs->end); // new pipeline
		globs->linecount = globs->linecount + k; // new linecount
	}
	free(temp);
	return (0);
}