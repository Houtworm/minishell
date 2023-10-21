/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:12:31 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/21 13:38:29 by djonker       ########   odam.nl         */
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

typedef struct s_shell		t_shell;
typedef struct s_forks		t_forks;
typedef struct s_commands	t_commands;
typedef struct s_globs		t_globs;
typedef struct s_builtin	t_builtin;
typedef struct s_alias		t_alias;

typedef struct s_alias
{
	char		*var;
	char		*val;
}	t_alias;

typedef struct s_builtin
{
	char		*cmnd;
	int			(*func)(t_commands cmd, t_shell *msh);
}	t_builtin;

typedef struct s_globs
{
	char		*line;
	char		*gsta;
	char		*gend;
	char		*start;
	char		*glob;
	char		*backup;
	char		*end;
	char		**sdir;
	char		**tmpsdir;
	char		*curdir;
	int			temptype;
	char		*pdir;
	char		**matches;
	int			linecount;
	int			matchcount;
	char		*anyof;
}	t_globs;

typedef struct s_commands
{
	int			forks;
	int			lastcode;
	int			condition;
	int			prio;
	int			infiles;
	char		**ofi;
	int			*append;
	char		*line;
	char		*absolute;
	char		**arg;
	int			code;
	int			cmds;
	int			debug;
}	t_commands;

typedef struct s_forks
{
	t_commands	*cmd;
	int			pid;
	char		*line;
	int			cmds;
	int			waitforlast;
}	t_forks;

typedef struct s_shell
{
	t_forks		*frk;
	t_alias		*alias;
	t_builtin	*bltn;
	char		*os;
	int			pid;
	char		*historyfile;
	char		*tmpdir;
	char		*sysfile;
	char		**envp;
	long long	starttime;
	int			**pipes;
	char		*oldline;
	char		*line;
	int			forks;
	int			code;
	int			debug;
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
char		*ft_cpnonquote(char *args, char *new, int *j, int *k);
int			ft_parseline(char *line, t_shell *msh, int forknumber);
int			ft_parsecommands(t_shell *msh, int forknumber, int cmdnumber);
// hashtag
char		*ft_parsehashtag(t_shell *msh);
// syntax
int			ft_checksyntax(t_shell *msh);
int			ft_startsyntax(t_shell *msh);
// pipe
t_shell		*ft_parsepipe(t_shell *msh);
// alias
void		ft_parsealiases(t_commands *cmd, t_shell msh);
// complete
char		*ft_completeline(t_shell *msh, int k, char *temp);
char		*ft_closeline(t_shell *msh, int quote, char *temp);
// quote
int			ft_checkoutquotevar(char *line);
int			ft_checkoutquote(char *line, char target, int mode);
int			ft_skipquote(char *s, int i);
char		check_quote_closed(t_shell *msh);
// heredoc
int			ft_heredoc(char *delimiter, char *file, t_shell msh, int heredoc);
void		ft_heredocinit(t_shell *msh, int ifrk, int icmd, char *strt);
// inputfile
int			ft_parseinputfiles(t_shell *msh, int forknumber);
char		*ft_getendinputfile(t_shell *msh, int forknumber, int icmd, int i);
void		ft_writefiletoinput(t_shell *msh, int frki, int icmd, char *file);
char		*ft_getfileinputfile(t_shell *msh, int f, int c, int i);
int			ft_getfilepos(t_shell *msh, int f, int c, int i);

// outputfile
int			ft_parseoutputfiles(t_commands *cmd);
// condition
int			ft_cpquote(char **cmdline, char	*forkline, int *icpip, int ifpip);
t_forks		ft_parseendcondition(t_shell *msh, int ifrk, int icmd, int ifpip);
//priority
int			ft_priority(t_commands *cmd, int cmdnbr, int i, int k);
// variable
char		*ft_parsevariable(char *line, t_shell msh, int quote);
// variable2
char		*ft_parsebegin(char *line, char *begin, int quote, int *i);
// tilde
char		*ft_parsetilde(char *line, t_shell msh);
// oldline
char		*ft_parseoldline(t_shell *msh);

// EXEC
// fork
int			ft_forktheforks(t_shell *msh);
// priority
void		ft_executepriority(t_commands *cmd, char **envp, char *sysfile);
// exec
int			ft_executeforks(int forknbr, t_shell *msh, int condition);
// dupmachine
int			ft_dupmachine(int cmdnbr, int forknbr, t_shell *msh);
//verify
int			ft_checkinputfile(char *inputfile);
int			ft_checkoutputfile(char *outputfile);
int			ft_checkcommand(char **arguments, char **envp);
//redirect
void		ft_redirectoutput(char **outf, int *appe, int ifrk, t_shell *msh);

// BUILTINS
// builtin
t_builtin	*ft_getbuiltins(void);
int			ft_builtincheck(t_commands cmd, int icmd, int ifrk, t_shell *msh);
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
int			ft_getglob(t_globs *globs, int startpos);
void		ft_matchtillglob(t_globs *g, char *dn, char *fp, unsigned char ty);
t_globs		*ft_initglobstruct(char *pipeline);
int			ft_skipbutcopygstart(t_globs *globs, int startpos);
void		ft_removequotesfromglobstart(t_globs *globs);
void		ft_removequotesfromglobend(t_globs *globs);
// globsub
int			ft_recursivematchsub(t_globs *globs, char *path, char *dnme, int i);
// globpoint
int			ft_nextsubglob(t_globs *globs, int subi, int reali, int globi);
int			ft_firstsubglob(t_globs *globs, struct dirent *dre, int si, int ri);
int			ft_nextglob(t_globs *globs, char *dname, int reali, int globi);
int			ft_firstglob(t_globs *globs, char *dname, int reali);
// globtools
void		ft_backupglob(t_globs *globs);
void		ft_cleanglob(t_globs *globs);
// globinitparent
int			ft_getparent(t_globs *globs);
void		ft_cleanpardir(t_globs *globs);
void		ft_removequotesfrompardir(t_globs *globs);

// globinitsubdir
void		ft_cleansubdir(t_globs *globs);
void		ft_removequotesfromsubdir(t_globs *globs);
void		ft_getsubdir(t_globs *globs);

// wildcard
int			ft_firstwildcard(t_globs *globs, char *dname, int reali);
int			ft_nextwildcard(t_globs *globs, char *dname, int reali, int globi);
// subwildcard
int			ft_firstsubwildcard(t_globs *g, struct dirent *dre, int si, int ri);
int			ft_nextsubwildcard(t_globs *globs, int subi, int reali, int globi);
// joker
int			ft_firstjoker(t_globs *globs, char *dname, int reali);
int			ft_nextjoker(t_globs *globs, char *dname, int reali, int globi);
// subjoker
int			ft_firstsubjoker(t_globs *g, struct dirent *dre, int si, int ri);
int			ft_nextsubjoker(t_globs *globs, int subi, int reali, int globi);
// anyof
int			ft_firstanyof(t_globs *globs, char *dname, int reali);
int			ft_nextanyof(t_globs *globs, char *dname, int reali, int globi);
// subanyof
int			ft_firstsubanyof(t_globs *g, struct dirent *dre, int si, int ri);
int			ft_nextsubanyof(t_globs *globs, int subi, int reali, int globi);
// globtools
int			ft_newpipeline(t_globs *globs);
void		ft_addglobmatch(t_globs *globs, char *match);

// TOOLS
// print
void		ft_printshell(t_shell msh);
void		ft_printforks(t_forks forks, int forknumber);
void		ft_printcommands(t_commands cmd, int cmdnbr, int forknbr);
void		ft_printglobs(t_globs globs, char *function);
void		ft_printdup(t_commands cmd, int cmdnbr, int forknbr);
// environment
char		**ft_setenv(char **envp, char *var, char *val);
char		**ft_fdtocharpp(t_shell *msh);
void		ft_charpptofd(char **array, t_shell *msh);
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
void		ft_createfdo(t_commands cmd);

#endif
