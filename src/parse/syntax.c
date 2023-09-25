/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   syntax.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 13:48:26 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/25 04:02:44 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_getinsults(void)
{
	char	**insults;

	insults = ft_calloc(100, 80);
	insults[0] = ft_strdup("Are you drunk or something? ");
	insults[1] = ft_strdup("Where did you learn how to type? ");
	insults[2] = ft_strdup("Is your keyboard broken? ");
	insults[3] = ft_strdup("Why don't you try a GUI? ");
	insults[4] = ft_strdup("What are you trying to do Yuka? ");
	insults[5] = ft_strdup("This is not a searchbar... ");
	insults[6] = ft_strdup("Monkeys shouldn't use this computer. ");
	insults[7] = ft_strdup("Why don't you go read the manual? ");
	insults[8] = ft_strdup("Even I know ");
	insults[9] = ft_strdup("Shell Licence revoked. ");
	insults[10] = ft_strdup("Adolf Hitler would be proud ");
	insults[11] = ft_strdup("Why don't you go back to your Mac? ");
	insults[12] = ft_strdup("You know Cocaine is bad for you right? ");
	insults[13] = ft_strdup("Your syntax illiteracy makes me a sad shell... ");
	insults[14] = ft_strdup("Everytime you do this a puppy dies a horrible death ");
	insults[15] = ft_strdup("Mi Inglash us coparible toe yoer sienthax ");
	insults[16] = ft_strdup("RTFM https://gnu.org/software/bash/manual ");
	insults[17] = ft_strdup("You just made me drown another kitten ");
	insults[18] = ft_strdup("I think a tamagotchi is better suited for you. ");
	insults[19] = ft_strdup("You are just wasting your time... ");
	return (insults);
}

int		ft_syntaxerror(t_shell *shell, char s1, char *line, int i)
{
	int		j;
	char	*help;
	char	**insults;
	int		random;

	ft_putstr_fd("Syntax Error: ", 2);
	insults = ft_getinsults();
	random = ft_gettimems(shell->envp) % 20;
	ft_putendl_fd(insults[random], 2);
	ft_putstr_fd("\nyou can't follow up this ", 2);
	ft_putchar_fd(s1, 2);
	ft_putendl_fd(" like that..", 2);
	help = ft_calloc(ft_strlen(line), 8);
	j = 0;
	while (j < i)
	{
		help[j] = ' ';
		j++;
	}
	help[j] = '^';
	help[j + 1] = '\0';
	ft_putendl_fd(line, 2);
	ft_putendl_fd(help, 2);
	shell->code = 2;
	ft_frearr(insults);
	free(help);
	return (1);
}

int		ft_checksymbol(char *line, int i)
{
	int		j;
	j = 1;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";>&|", line[i + j]))
		return (0);
	return (j);
}

int		ft_checksymbols(char *line, int i, char symbol)
{
	int		j;
	j = 1;
	if (line[i + j] == symbol)
		j++;
	while (line[i + j] == ' ')
		j++;
	if (line[i + j] && ft_strchr(";>&|", line[i + j]))
		return (0);
	return (j);
}

int		ft_checksyntax(t_shell *shell, char *line)
{
	int	i;
	int	t;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("<>&|;", line[i]))
		{
			if (line[i] == '<')
			{
				t = ft_checksymbols(line, i, '<');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '<', line, i));
			}
			if (line[i] == '>')
			{
				t = ft_checksymbols(line, i, '>');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '>', line, i));
			}
			if (line[i] == '&')
			{
				t = ft_checksymbols(line, i, '&');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '&', line, i));
			}
			if (line[i] == '|')
			{
				t = ft_checksymbols(line, i, '|');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '|', line, i));
			}
			if (line[i] == ';')
			{
				t = ft_checksymbol(line, i);
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, ';', line, i));
			}
		}
		i++;
	}
	return (0);
}
