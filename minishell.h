/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/08/26 04:15:15 by djonker      \___)=(___/                 */
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

// Structs

typedef struct s_redirect
{
	int					fd_in; // -1 for heredoc?
	int					fd_out;
	char				*infilename;
	char				*outfilename;
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
	int			lastcode;
	t_redirect	*redirect;
}	t_cmds;

typedef struct s_forks
{
	t_cmds		*cmds;
	char		*pipeline; //command line separated by pipe
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

// MAIN
// main
int	main(int argc, char **argv, char **envp);
int	ft_mainloop(t_shell *shell, char **envp);
void	ft_sighandler(int sig);

// TOOLS
// tools
long long	ft_gettimems(char **envp);
// env
int	ft_setenv(char **envp, char *var, char *val);
// error
int	ft_errorexit(char *reason, char *cmd, int code);

// INIT
// init
t_shell	*ft_initstruct(char **envp);
// prompt
void	ft_printprompt(t_shell *strct, char **envp);
char	*ft_addosuserandhosttoprompt(char **envp);
char	*ft_addworkingdirectory(char *prompt, char **envp);
char	*ft_addexecutiontime(t_shell *shell, char *temp, char **envp);
char	*ft_addreturncode(t_shell *shell, char *temp);
// script
int	ft_runscript(int argc, char **argv, char **envp);


// PARSE
// parse
int	*ft_parseline(char *line, t_shell *shell);
//parse_1
int		check_quote_closed(char *s);
int		count_str(char *s, int c);
int		count_wd(char *s, int c);
char	**split_not_quote(char *s, int c);
//parse_2
t_forks	*ft_forks_strct(char *line, t_shell *shell);
t_cmds	*ft_exec_strct(char *pipeline, t_forks forks);
// void	ft_strct_per_cmd(char **cmds, t_shell *shell);
//redirect
void	ft_check_redirect(t_cmds cmds, char *command);
t_redirect	*ft_redrc_in(t_cmds cmds, char *meta, char *file);
t_redirect	*ft_redrc_out(t_cmds cmds, char *meta, char *file);
void	ft_rdrct_add_back(t_redirect **lst, t_redirect *new);
//exec_strct
int	symbol_check(char	*s);
int	count_str2(char *s);
int	count_wd2(char *s);
char	**split_spchr(char *s);

// EXEC
// fork
int	ft_forktheforks(t_shell *shell);
// exec
int	ft_builtincheck(t_cmds cmds);
int	ft_executecommand(t_cmds cmds);
int	ft_executeforks(t_forks forks);
// dupmachine
int	ft_dupmachine(t_cmds cmds);
int	ft_heredoc(char *delimiter);
//verify
int	ft_checkinputfile(char *inputfile);
int	ft_checkoutputfile(char *outputfile);
int	ft_checkcommand(t_cmds cmds);

// builtins
int	ft_chdir(t_cmds cmds);
int	ft_exit(t_cmds cmds);
int	ft_unset(t_cmds cmds);
int	ft_export(t_cmds cmds);
int	ft_env(t_cmds cmds);
int	ft_pwd(t_cmds cmds);
int	ft_echo(t_cmds cmds);

#endif
