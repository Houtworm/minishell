/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                     |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarkoh <fsarkoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 07:20:24 by houtworm          #+#    #+#             */
/*   Updated: 2023/05/29 22:20:47 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Headers

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "getnextline/get_next_line.h"
# include <stdio.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS	0
# define ERROR		1

# define TRUE		1
# define FALSE		0

# define SHELL_PROMPT	"❯ "

// Structs

typedef struct s_exec
{
	char		**envp;
	char		*absolute;
	char		**arguments;
	int			redirectfrom;
	int			redirectto;
	int			detatch;
	int			andop;
	int			orop;
//	int			tofd;
//	int			fromfd;
}	t_exec;

typedef struct s_forks
{
	t_exec		*commands;
}	t_forks;

typedef struct s_shell
{
	t_forks		*forks;
	char		**envp;
	long long	starttime;
	int			code;
	char		*line;
	char		*absolute;
	char		**arguments;
}	t_shell;

// Prototypes

// Move to libft

int	ft_setenv(char **envp, char *var, char *val);
long long	ft_gettimems(char **envp);

// init

t_shell	*ft_initstruct(char **envp);

// prompt

void	ft_printprompt(t_shell *strct, char **envp);

// parse

int	*ft_parseline(char *line, t_shell *strct);

// execute

int	ft_executecommands(t_shell *strct);

// script

int	ft_runscript(int argc, char **argv, char **envp);

// builtins

int	ft_chdir(t_shell *strct);
int	ft_exit(t_shell *strct);
int	ft_unset(t_shell *strct);
int	ft_export(t_shell *strct);
int	ft_env(t_shell *strct);
int	ft_pwd(t_shell *strct);
int	ft_echo(t_shell *strct);

#endif
