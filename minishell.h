/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/25 04:57:54 by houtworm     \___)=(___/                 */
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
	int					fd_in; // -1 for heredoc?
	int					fd_out;
	int					trc_apd; //0 for trunc, 1 for append, 2 for just touch (if it should remain empty)
	char				*heredocdelimiter; // the EOF thingy in heredoc :)
	struct s_redirect	*nxt;
}	t_redirect;

typedef struct s_cmds
{
	char		**envp;
	char		*absolute;
	char		**arguments;
	int			detatch;
	int			condition; // 0 for non, 1 for &&, 2 for || 
	int			pid;
	int			code;
	t_redirect	*redirect;
}	t_cmds;

typedef struct s_forks
{
	t_cmds		*cmds;
	int			pid;
	int			cmdamount;
}	t_forks;

typedef struct s_shell
{
	t_forks		*forks;
	char		**envp;
	long long	starttime;
	int			code;
	int			forkamount; // 1 fork struct is 1, 2 fork structs is 2. so start from 1, and ++ for every additional fork :)
	char		*line;
}	t_shell;

// Prototypes

// Tools

int	ft_setenv(char **envp, char *var, char *val);
long long	ft_gettimems(char **envp);
int	ft_errorexit(char *reason, char *cmd, int code);

// init

t_shell	*ft_initstruct(char **envp);
void	ft_printprompt(t_shell *strct, char **envp);
int	ft_runscript(int argc, char **argv, char **envp);

// parse
int	*ft_parseline(char *line, t_shell *shell);

//parse_1
int		check_quote_closed(char *s);
int		count_str(char *s, int c);
int		count_wd(char *s, int c);
char	**split_not_quote(char *s, int c);

//parse_2
void	ft_strct_per_cmd(char **cmds, t_shell *shell);

//redirect
void	ft_check_redirect(t_cmds cmds, char *command);
t_redirect	*ft_redrc_in(t_cmds cmds, char *meta, char *file);
t_redirect	*ft_redrc_out(t_cmds cmds, char *meta, char *file);
void	ft_rdrct_add_back(t_redirect **lst, t_redirect *new);

// exec
int	ft_forktheforks(t_shell *shell);
int	ft_dupmachine(t_cmds cmds);

// builtins
int	ft_chdir(t_cmds cmds);
int	ft_exit(t_cmds cmds);
int	ft_unset(t_cmds cmds);
int	ft_export(t_cmds cmds);
int	ft_env(t_cmds cmds);
int	ft_pwd(t_cmds cmds);
int	ft_echo(t_cmds cmds);

#endif
