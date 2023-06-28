/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsarkoh <fsarkoh@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 13:20:31 by houtworm      #+#    #+#                 */
/*   Updated: 2023/06/28 18:53:05 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_procwildcards(t_shell *strct)
{

	strct++;
}

void	ft_procsquarebrack(t_shell *strct)
{
	char	*line;
	int		i;
	int		options[256];

	i = 0;
	line = strct->line;
	while (*line)
	{
		// somehow save characters before [
		while (*line && *line != '[')
			line++;
		line++;
		while (*line && *line != ']')
		{
			options[i] = (int)*line;
			i++;
		}
		i = options[0];
		/*if (*line)*/
			//  options and expand to the files that match
	}
}

int	ft_chrstrexquo(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
				s++;
		}
		if (*s == '\"')
		{
			s++;
			while (*s != '\"')
				s++;
		}
		s++;
	}
	if (c == *s)
		return (1);
	return (0);
}

void	ft_expandcommands(t_shell *strct)
{
	/*int		i;*/

	/*i = 0;*/
	if (ft_chrstrexquo('[', strct->line))
	{
		ft_procsquarebrack(strct);
	}
	/*if (ft_chrstrexquo('?', strct->line))*/
	/*{*/
		/*ft_procquestionmark(strct);*/
	/*}*/
	/*if (ft_chrstrexquo('*', strct->line))*/
	/*{*/
		/*ft_procwildcard(strct);*/
	/*}*/
	/*if (ft_chrstrexquo('`', strct->line))*/
	/*{*/
		/*ft_proccmdsubst(strct);*/
	/*}*/
}

void	ft_strct_per_cmd(char **line, t_shell *shell)
{
	int	i;
	char	**tmp;
	t_forks	*forks;

	i = 0;
	while (line[i])
	{
		tmp = ft_split(line[i], '|');
		while (tmp)
		{
			
		}
		ft_frearr(tmp);
		i++;
	}
}


//example commandline 
// cat < file1 | grep a | wc -l > file2 > file3 ; echo "hello; world | hey" | grep e; echo b
int	*ft_parseline(char *line, t_shell *shell)
{
	char	**paths;
	char	**semicolon_tmp;

	shell->line = line;
	// 1. look for quotes, check if it's properly clsoed, split based on quote
	// 2. separate based on semicolon
	// 3. 
	/*ft_expandcommands(strct);*/
	 /*expand * outside quotes;*/
	// expand ? outside quotes;
	// expand [] outside quotes
	// expand ` outside quotes
	// expand $ only not in single quote
	// check for |, ;, &, ||, && not in quotes in every fork->line and do the following depending on the character in order of the string
	// on | remove character split rest of string into next fork
	// on ; remove character split rest of string into next command
	// on & remove character split rest of string into next command and flag background
	// on || remove characters split rest of string into next command with condition
	// on && remove characters split rest of string into next command with condition
	// look for < >> > in all commands and set up dup2  where needed
	// look for << and <<< Heredoc and Herestring
	// split ever command up into absolute and arguments for execve
	shell->arguments = ft_split(line, ' ');
	paths = ft_getpaths(shell->envp, 1);
	shell->absolute = ft_abspathcmd(paths, shell->arguments[0]);
	ft_frearr(paths);
	return (SUCCESS);
}

// Order
// parse quotes
// parse ; special character
// parse special operators {} () < > << >> <<< | [] ? & && || 
// parse expansion * $NAME $(command) 
//
// < Makefile cat  | grep CFLAGS > out
// echo $NAME | $(which cat) >> out 
// << EOF `which cat` | wc -l 
// cat * && cat ? || cat file[123]
//
// Expand Every $ not in single quotes $VAR execute $() beforehand and replace the value
// Split on pipe pipe1 pipe2 pipe3 if pipe prepare pipes and run pipes at the same time
// split all pipes on ; put commands in pipe struct
// check if command needs to be redirected if so set up the proper pipes
// Check if any command needs to be detatched
//
