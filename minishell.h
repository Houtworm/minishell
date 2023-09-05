/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/06 00:24:22 by djonker      \___)=(___/                 */
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
	char				*infilename;
	char				*outfilename;
	int					append; //0 for trunc, 1 for append, 2 for just touch (if it should remain empty)
	char				*delimiter; // the EOF thingy in heredoc :)
	struct s_redirect	*nxt;
}	t_redirect;

typedef struct s_alias
{
	char		*var;
	char		*val;
}	t_alias;

typedef struct s_globs
{
	char		*gstart;
	char		*gend;
	char		*start;
	char		*glob;
	char		*end;
	char		*subdir;
	char		*pardir;
	char		*matches;
	char		*pipeline;
	int			period;
	int			linecount;
}	t_globs;

typedef struct s_cmds
{
	char		**envp;
	int			envpfd;
	char		*absolute;
	char		**arguments;
	int			detatch;
	char		*pipeline;
	int			condition; // 0 for non, 1 for &&, 2 for || 
	int			pid;
	int			code;
	int			lastcode;
	int			debug;
	int			cmdamount;
	int			forkamount;
	t_redirect	*redirect;
}	t_cmds;

typedef struct s_forks
{
	t_cmds		*cmds;
	char		*pipeline;
	int			pid;
	int			cmdamount;
}	t_forks;

typedef struct s_shell
{
	t_forks		*forks;
	t_alias		*alias;
	int			envpfd;
	char		**envp;
	long long	starttime;
	int			code;
	int			debug;
	int			**pipes;
	int			forkamount;
	char		*line;
}	t_shell;

// Prototypes

// MAIN
// main
int			main(int argc, char **argv, char **envp);

// TOOLS
// tools
long long	ft_gettimems(char **envp);
// print
void		ft_printshell(t_shell shell);
void		ft_printforks(t_forks forks, int forknumber);
void		ft_printcmds(t_cmds cmds, int cmdnbr, int forknbr);
void		ft_printglobs(t_globs globs, char *function);
void		ft_printdup(t_cmds cmds, int cmdnbr, int forknbr);
// env
int			ft_setenv(char **envp, char *var, char *val);
char		**ft_fdtocharpp(int	fd);
void		ft_charpptofd(char **array, int fd);
// error
int			ft_errorexit(char *reason, char *cmd, int code);
int			ft_moderrorexit(char *reason, char *cmd, char *cmd2, int code);

// INIT
// init
t_shell		*ft_initstruct(char **envp, int debugmode);
// prompt
void		ft_printprompt(t_shell *strct, char **envp);
// script
int			ft_runscript(int argc, char **argv, char **envp);

// PARSE
//parse
t_shell		ft_parseline(char *line, t_shell shell);
t_shell 	ft_parsecmds(t_shell shell, int forknumber, int cmdnumber);
//hashtag
char		*ft_parsehashtag(char *line);
//pipe
t_shell 	ft_parsepipe(char *line, t_shell shell);
//alias
void		ft_parsealiases(t_cmds *cmds, t_shell shell);
//quote
char		*ft_closequote(char *line);
char	**ft_remove_quote(char	**cmd, int count);
//redirect
void		ft_check_redirect(t_cmds *cmds);
t_redirect *ft_redrc_in(t_redirect *redirect, char *file);
t_redirect *ft_redrc_out(t_redirect *redirect, char *file);
void		ft_rdrct_add_back(t_redirect **lst, t_redirect *new);
//condition
t_forks		ft_parseendcondition(t_forks forks);
void	ft_copyquote(char **cmdline, char	*forkline, int icpip, int ifpip);
int		ft_countendconditions(char *line, int count, int i);
//variable
int 		ft_parsevariable(t_cmds *cmd, t_shell shell);
//globs
int			ft_parseglobs(t_cmds *cmd);
//wildcard
void		ft_parsewildcard(t_cmds cmd, t_globs *globs);
//tools
int			ft_checkoutquote(char *line, char target, int mode);
//parse_utils
int			check_quote_closed(char *s);
int			ft_skipquote(char *s, int i);
int			count_str(char *s, int c);
int			count_wd(char *s, int c);
char		**split_not_quote(char *s, int c);
//struct
//t_forks		*ft_parsespchr(t_forks *forks, t_shell *shell);
//t_forks 	*ft_parsepipe(char *line, t_shell *shell);
//t_forks		ft_fill_teststrct(t_forks forks, t_shell *shell, char *cmd, int cmdamount);
//exec_strct
//int			symbol_check(char	*s);
//int			count_str2(char *s);
//int			count_wd2(char *s);
//char		**split_spchr(char *s);

// EXEC
// fork
int			ft_forktheforks(t_shell *shell);
// priority
void		ft_executepriority(t_cmds *cmd);
// exec
int			ft_executeforks(int forknbr, t_shell *shell);
// dupmachine
int			ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell);
//verify
int			ft_checkinputfile(char *inputfile);
int			ft_checkoutputfile(char *outputfile);
int			ft_checkcommand(t_cmds cmds);

// BUILTINS
// chdir
int			ft_chdir(t_cmds cmds);
// exit
int			ft_exit(t_cmds cmds);
// unset
int			ft_unset(t_cmds cmds);
// export
int			ft_export(t_cmds cmds);
// env
int			ft_env(void);
// pwd
int			ft_pwd(t_cmds cmds);
// echo
int			ft_echo(t_cmds cmds);

#endif
