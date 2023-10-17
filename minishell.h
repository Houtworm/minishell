/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/17 16:30:45 by houtworm     \___)=(___/                 */
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
typedef struct s_commands t_commands;
typedef struct s_globs t_globs;
typedef struct s_builtin t_builtin;
typedef struct s_alias t_alias;

typedef struct s_alias
{
	char		*var;
	char		*val;
}	t_alias;

typedef struct	s_builtin
{
	char		*cmnd;
	int			(*func)(t_commands cmd, t_shell *msh);
}	t_builtin;

typedef struct s_globs
{
	char		*gstart;
	char		*gend;
	char		*start;
	char		*glob;
	char		*backup;
	char		*end;
	char		**subdir;
	char		**tempsubdir;
	char		*curdir;
	int			temptype;
	char		*pardir;
	char		**matches;
	char		*line;
	char		*subdirs;
	int			linecount;
	int			matchcount;
	char		*anyof;
}	t_globs;

typedef struct s_commands
{
	char		*absolute;
	char		**arg;
	int			detatch;
	char		*line;
	int			condition;
	int			pid;
	int			code;
	int			lastcode;
	int			debug;
	int			cmdamount;
	int			forkamount;
	//char		**infile;
	char		**outfile;
	int			*append;
	int			input;
	int			prio;
}	t_commands;

typedef struct s_forks
{
	t_commands	*cmd;
	char		*line;
	int			pid;
	int			cmdamount;
	int			waitforlast;
}	t_forks;

typedef struct s_shell
{
	t_forks		*frk;
	t_alias		*alias;
	t_builtin	*bltn;
	int			envpfd;
	char		**envp;
	long long	starttime;
	int			code;
	int			debug;
	int			**pipes;
	int			forkamount;
	int			stdincount;
	int			stop;
	int			pid;
	char		*line;
	char		*os;
	char		*historyfile;
	char		*oldline;
	char		*tmpdir;
}	t_shell;

// Prototypes

// MAIN
// main
int			main(int argc, char **argv, char **envp);
// init
t_shell		*ft_initstruct(char **envp, int debugmode);
// prompt
void		ft_printprompt(t_shell *msh, char **envp);
// signal
void		ft_sighandler(int sig);
int			ft_sighook(void);
// mshrc
t_alias		*ft_parsemshrc(char **envp);
// history
void		ft_writehistory(char *line, char *file, t_shell *msh);
void		ft_readhistory(char *file);
// insults
void		ft_printinsult(t_shell *msh);

// PARSE
// parse
int			ft_parseline(char *line, t_shell *msh);
t_shell 	*ft_parsecommands(t_shell *msh, int forknumber, int cmdnumber);
// hashtag
char		*ft_parsehashtag(t_shell *msh);
// syntax
int			ft_checksyntax(t_shell *msh);
int			ft_startsyntax(t_shell *msh);
// pipe
t_shell 	*ft_parsepipe(t_shell *msh);
// alias
void		ft_parsealiases(t_commands *cmd, t_shell msh);
// complete
char		*ft_completeline(t_shell *msh, int k);
char		*ft_closeline(t_shell *msh);
// quote
int			ft_checkoutquotevar(char *line);
int			ft_checkoutquote(char *line, char target, int mode);
int			ft_skipquote(char *s, int i);
char		check_quote_closed(t_shell *msh);
// heredoc
int			ft_heredoc(char **delimiter, char *file, t_shell msh, int heredoc);
// inputfile
int			ft_parseinputfiles(t_shell *msh, int forknumber);
// outputfile
int			ft_parseoutputfiles(t_commands *cmd);
// condition
void		ft_copyquote(char **cmdline, char	*forkline, int icpip, int ifpip);
t_forks		ft_parseendcondition(t_shell *msh, int forknumber);
//priority
int 		ft_priority(t_commands *cmd, int cmdnbr);
// variable
int 		ft_parsevariable(t_commands *cmd, t_shell msh);
//int 		ft_parsevariable(t_shell *msh, int forknumber);
// tilde
char		*ft_parsetilde(char *line, t_shell msh);
//void		ft_parsetilde(t_shell *msh, int forknumber);
// oldline
char		*ft_parseoldline(t_shell *msh);

// EXEC
// fork
int			ft_forktheforks(t_shell *msh);
// priority
void		ft_executepriority(t_commands *cmd, char **envp);
// exec
int			ft_executeforks(int forknbr, t_shell *msh, int condition);
// dupmachine
int			ft_dupmachine(int cmdnbr, int forknbr, t_shell *msh);
//verify
int			ft_checkinputfile(char *inputfile);
int			ft_checkoutputfile(char *outputfile);
int			ft_checkcommand(char **arguments, char **envp);

// BUILTINS
// builtin
t_builtin	*ft_getbuiltins(void);
int			ft_builtincheck(t_commands cmd, int cmdnbr, int forknbr, t_shell *msh);
int			ft_alias(t_commands cmd, t_shell *msh);
int			ft_chdir(t_commands cmd, t_shell *msh);
int			ft_exit(t_commands cmd, t_shell *msh);
int			ft_unset(t_commands cmd, t_shell *msh);
int			ft_export(t_commands cmd, t_shell *msh);
int			ft_env(t_commands cmd, t_shell *msh);
int			ft_pwd(t_commands cmd, t_shell *msh);
int			ft_echo(t_commands cmd, t_shell *msh);
int			ft_z(t_commands cmd, t_shell *msh);
int			ft_period(t_commands cmd, t_shell *msh);
int			ft_exec(t_commands cmd, t_shell *msh);
int			ft_which(t_commands cmd, t_shell *msh);

// GLOBS
// globs
int			ft_parseglobs(t_commands *cmd, char **envp);
// globinit
void		ft_getsubdir(t_globs *globs);
int			ft_getparent(t_globs *globs);
int			ft_getglob(t_globs *globs, int startpos);
t_globs 	*ft_initglobstruct(char *pipeline);
// globsub
int			ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i);
// globpoint
int			ft_nextsubglob(t_globs *globs, int subi, int reali, int globi);
int			ft_firstsubglob(t_globs *globs, struct dirent *dirents, int subi, int reali);
int			ft_nextglob(t_globs *globs, char *dname, int reali, int globi);
int			ft_firstglob(t_globs *globs, char *dname, int reali);
// globtools
int			ft_newpipeline(t_globs *globs);
void		ft_addglobmatch(t_globs *globs, char *match);
void		ft_backupglob(t_globs *globs);
void		ft_cleanglob(t_globs *globs);
// wildcard
int			ft_nextsubwildcard(t_globs *globs, int subi, int reali, int globi);
int			ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int subi, int reali);
int			ft_nextwildcard(t_globs *globs, char *dname, int reali, int globi);
int			ft_firstwildcard(t_globs *globs, char *dname, int reali);
// joker
int			ft_nextsubjoker(t_globs *globs, int subi, int reali, int globi);
int			ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int subi, int reali);
int			ft_nextjoker(t_globs *globs, char *dname, int reali, int globi);
int			ft_firstjoker(t_globs *globs, char *dname, int reali);
// anyof
int			ft_nextsubanyof(t_globs *globs, int subi, int reali, int globi);
int			ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int subi, int reali);
int			ft_nextanyof(t_globs *globs, char *dname, int reali, int globi);
int			ft_firstanyof(t_globs *globs, char *dname, int reali);

// TOOLS
// time
long long	ft_gettimems(char **envp);
// print
void		ft_printshell(t_shell msh);
void		ft_printforks(t_forks forks, int forknumber);
void		ft_printcommands(t_commands cmd, int cmdnbr, int forknbr);
void		ft_printglobs(t_globs globs, char *function);
void		ft_printdup(t_commands cmd, int cmdnbr, int forknbr);
// environment
char		**ft_setenv(char **envp, char *var, char *val);
char		**ft_fdtocharpp(int	fd, t_shell *msh);
void		ft_charpptofd(char **array, int fd, t_shell *msh);
// files
int			ft_mkdir(char *dirname, char **envp);
int			ft_rmdir(char *dirname, char **envp);
// error
int			ft_errorexit(char *reason, char *cmd, int code);
int			ft_errorexit2(char *reason, char *cmd, char *cmd2, int code);
int			ft_errorret(char *reason, char *cmd, int code);
int			ft_errorret2(char *reason, char *cmd, char *cmd2, int code);
// cleanup
void		ft_freeexit(t_shell *msh, int code);
void		ft_freeglobs(t_globs *globs);
void		ft_freenewprompt(t_shell *msh);
// fd
void		ft_safeclosefd(int	fd);
void		ft_closepipes(t_shell *msh);
void		ft_restorefds(t_shell *msh);
void		ft_createfdo(t_commands cmd);
// semaphore
int			ft_seminit(char *file, int number);
int			ft_semwait(char *file);
int			ft_semfree(char *file);

#endif
