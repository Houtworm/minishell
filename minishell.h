/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/24 15:15:51 by yitoh         ########   odam.nl         */
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

typedef struct s_redirect
{
	int					fd_in;
	int					fd_out;
	int					trc_apd; //0 for trunc, 1 for append
	struct s_redirect	*nxt;
}	t_redirect;

typedef struct s_exec
{
	char		**envp;
	char		*absolute;
	char		**arguments;
	int			detatch;
	int			condition; // 0 for non, 1 for &&, 2 for || 
	t_redirect	*redirect;
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


//parse_1
int		check_quote_closed(char *s);
int		count_str(char *s, int c);
int		count_wd(char *s, int c);
char	**split_not_quote(char *s, int c);

//parse_2
void	ft_strct_per_cmd(char **cmd, t_shell *shell);

//redirect
void	ft_check_redirect(t_exec commands, char *cmd);
t_redirect	*ft_redrc_in(t_exec commands, char *meta, char *file);
t_redirect	*ft_redrc_out(t_exec commands, char *meta, char *file);
void	ft_rdrct_add_back(t_redirect **lst, t_redirect *new);

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

//test


#endif
