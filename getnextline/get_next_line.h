/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 06:09:11 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 16:55:31 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 300
# endif

struct s_gnl
{
	char		b[BUFFER_SIZE + 1];
	int			fd;
};

int				get_next_line(int fd, char **line);
int				findnewline(struct s_gnl *strct);
int				newline(struct s_gnl *strct, char **line);
int				blimit(int l, struct s_gnl *strct, char **line, char *t);;
int				nonewline(int l, struct s_gnl *strct, char **line);
char			*gnl_substr(char const *s, unsigned int start, size_t len);
void			*gnl_memcpy(void *dst, const void *src, size_t n);
size_t			gnl_strlen(char *str);
void			gnl_bzero(void *s, size_t n);
char			*gnl_strjoin(char const *s1, char const *s2);

#endif
