/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 18:17:02 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/25 03:00:50 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checksmallerthan(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '<' || line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (ft_strchr(";<&|", line[i + j]))
		return (ft_syntaxerror(msh, '<', line, i));
	return (0);
}

int	ft_checkmorethan(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '>')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (ft_strchr(";<>&|", line[i + j]))
		return (ft_syntaxerror(msh, '>', line, i));
	return (0);
}

int	ft_checkampersand(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '&')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, '&', line, i));
	return (0);
}

int	ft_checkpipe(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	if (line[i + j] == '|')
		j++;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, '|', line, i));
	return (0);
}

int	ft_checksmcolon(t_shell *msh, char *line, int i)
{
	int		j;

	j = 1;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";&|", line[i + j]))
		return (ft_syntaxerror(msh, ';', line, i));
	return (0);
}
