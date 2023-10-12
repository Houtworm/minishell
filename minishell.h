/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/12 12:38:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Headers

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "getnextline/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/termios.h>
# include <readline/readline.h>
# include <readline/history.h>

// Structs

typedef struct s_shell t_shell;
typedef struct s_forks t_forks;
typedef struct s_cmds t_cmds;
typedef struct s_globs t_globs;
typedef struct s_builtin t_builtin;
typedef struct s_alias t_alias;

typedef struct s_alias
{
	char	*var;
	char	*val;
}	t_alias;

typedef struct	s_builtin
{
	char	*compare;
	int		(*func)(t_cmds cmds, t_shell *shell);
}	t_builtin;

typedef struct s_globs
{
	char	*gstart;
	char	*gend;
	char	*start;
	char	*glob;
	char	*backup;
	char	*end;
	char	**subdir;
	char	**tempsubdir;
	char	*curdir;
	int		temptype;
	char	*pardir;
	char	**matches;
	char	*pipeline;
	char	*subdirs;
	int		linecount;
	int		matchcount;
	char	*anyof;
}	t_globs;

typedef struct s_cmds
{
	char	*absolute;
	char	**arguments;
	int		detatch;
	char	*pipeline;
	int		condition;
	int		pid;
	int		code;
	int		lastcode;
	int		debug;
	int		cmdamount;
	int		forkamount;
	char	**infile;
	char	**outfile;
	int		*append;
	int		hdfd;
	int		prio;	
}	t_cmds;

typedef struct s_forks
{
	t_cmds	*cmds;
	char	*pipeline;
	int		pid;
	int		cmdamount;
}	t_forks;

typedef struct s_shell
{
	t_forks		*forks;
	t_alias		*alias;
	t_builtin	*builtins;
	int			envpfd;
	int			hdfd; // whu?
	char		**envp;
	long long	starttime;
	int			code;
	int			debug;
	int			**pipes;
	int			forkamount;
	int			stop;
	int			pid;
	char		*line;
	char		*os;
	char		*historyfile;
	char		*oldline;
	int			stdinfd;
	int			stdoutfd;
}	t_shell;

// Prototypes

// MAIN
// main
int			main(int argc, char **argv, char **envp);
// init
t_shell		*ft_initstruct(char **envp, int debugmode);
// prompt
void		ft_printprompt(t_shell *strct, char **envp);
// script
int			ft_runscript(int argc, char **argv, t_shell *shell);
// signal
void		ft_sighandler(int sig);
int			ft_sighook(void);
// mshrc
t_alias		*ft_parsemshrc(char **envp);
// history
void		ft_writehistory(char *line, char *file);
void		ft_readhistory(char *file);
// insults
void		ft_printinsult(t_shell *shell);

// PARSE
// parse
int			ft_parseline(char *line, t_shell *shell);
t_shell 	*ft_parsecmds(t_shell *shell, int forknumber, int cmdnumber);
// hashtag
char		*ft_parsehashtag(t_shell *shell);
// syntax
int			ft_checksyntax(t_shell *shell);
int			ft_startsyntax(t_shell *shell);
// pipe
t_shell 	*ft_parsepipe(t_shell *shell);
// alias
void		ft_parsealiases(t_cmds *cmds, t_shell shell);
// complete
char		*ft_completeline(t_shell *shell, int k);
char		*ft_closeline(t_shell *shell);
// quote
int			ft_checkoutquotevar(char *line);
int			ft_checkoutquote(char *line, char target, int mode);
int			ft_skipquote(char *s, int i);
char		check_quote_closed(t_shell *shell);
// heredoc
t_forks		ft_parseheredoc(t_shell *shell, int forknumber);
// redirect
int			ft_parseredirection(t_cmds *cmds);
// condition
void		ft_copyquote(char **cmdline, char	*forkline, int icpip, int ifpip);
t_forks		ft_parseendcondition(t_shell *shell, int forknumber);
//priority
int 		ft_priority(t_cmds *cmds, int cmdnbr);
// variable
int 		ft_parsevariable(t_cmds *cmd, t_shell shell);
// tilde
void		ft_parsetilde(t_cmds *cmds, t_shell shell);
// oldline
char		*ft_parseoldline(t_shell *shell);

// EXEC
// fork
int			ft_forktheforks(t_shell *shell);
// priority
void		ft_executepriority(t_cmds *cmd, char **envp);
// exec
int			ft_executeforks(int forknbr, t_shell *shell, int condition);
// dupmachine
int			ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell);
//verify
int			ft_checkinputfile(char *inputfile);
int			ft_checkoutputfile(char *outputfile);
int			ft_checkcommand(t_cmds cmds, char **envp);

// BUILTINS
// builtin
t_builtin	*ft_getbuiltins(void);
int			ft_builtincheck(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell);
int			ft_alias(t_cmds cmd, t_shell *shell);
int			ft_chdir(t_cmds cmds, t_shell *shell);
int			ft_exit(t_cmds cmds, t_shell *shell);
int			ft_unset(t_cmds cmds, t_shell *shell);
int			ft_export(t_cmds cmds, t_shell *shell);
int			ft_env(t_cmds cmds, t_shell *shell);
int			ft_pwd(t_cmds cmds, t_shell *shell);
int			ft_echo(t_cmds cmds, t_shell *shell);
int			ft_z(t_cmds cmds, t_shell *shell);
int			ft_period(t_cmds cmds, t_shell *shell);
int			ft_exec(t_cmds cmds, t_shell *shell);
int			ft_which(t_cmds cmds, t_shell *shell);

// GLOBS
// globs
int			ft_parseglobs(t_cmds *cmd, char **envp);
// globinit
void		ft_getsubdir(t_globs *globs);
int			ft_getparent(t_globs *globs);
int			ft_getglob(t_globs *globs, int startpos);
t_globs 	*ft_initglobstruct(char *pipeline);
// globsub
int			ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i);
// globpoint
int			ft_nextsubglob(t_globs *globs, int i, int j, int k);
int			ft_firstsubglob(t_globs *globs, struct dirent *dirents, int i, int j);
int			ft_nextglob(t_globs *globs, char *dname, int i, int j);
int			ft_firstglob(t_globs *globs, char *dname, int i);
// globtools
int			ft_newpipeline(t_globs *globs);
void		ft_addglobmatch(t_globs *globs, char *match);
void		ft_backupglob(t_globs *globs);
void		ft_cleanglob(t_globs *globs);
// wildcard
int			ft_nextsubwildcard(t_globs *globs, int i, int j, int k);
int			ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int i, int j);
int			ft_nextwildcard(t_globs *globs, char *dname, int i, int j);
 int		ft_firstwildcard(t_globs *globs, char *dname, int i);
// joker
int			ft_nextsubjoker(t_globs *globs, int i, int j, int k);
int			ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int i, int j);
int			ft_nextjoker(t_globs *globs, char *dname, int i, int j);
 int		ft_firstjoker(t_globs *globs, char *dname, int i);
// anyof
int			ft_nextsubanyof(t_globs *globs, int i, int j, int k);
int			ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int i, int j);
int			ft_nextanyof(t_globs *globs, char *dname, int i, int j);
 int		ft_firstanyof(t_globs *globs, char *dname, int i);

// TOOLS
// time
long long	ft_gettimems(char **envp);
// print
void		ft_printshell(t_shell shell);
void		ft_printforks(t_forks forks, int forknumber);
void		ft_printcmds(t_cmds cmds, int cmdnbr, int forknbr);
void		ft_printglobs(t_globs globs, char *function);
void		ft_printdup(t_cmds cmds, int cmdnbr, int forknbr);
// environment
char		**ft_setenv(char **envp, char *var, char *val);
char		**ft_fdtocharpp(int	fd);
void		ft_charpptofd(char **array, int fd);
// error
int			ft_errorexit(char *reason, char *cmd, int code);
int			ft_moderrorexit(char *reason, char *cmd, char *cmd2, int code);
int			ft_errorreturn(char *reason, char *cmd, int code);
int			ft_moderrorreturn(char *reason, char *cmd, char *cmd2, int code);
// cleanup
void		ft_freeexit(t_shell *shell, int code);
void		ft_freeglobs(t_globs *globs);
void		ft_freenewprompt(t_shell *shell);
// fd
void		ft_safeclosefd(int	fd);
void		ft_closepipes(t_shell *shell);
void		ft_restorefds(t_shell *shell);
void		ft_createfdo(t_cmds cmd);
// semaphore
int			ft_seminit(char *file, int number);
int			ft_semwait(char *file);
int			ft_semfree(char *file);

#endif
