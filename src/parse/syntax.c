/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   syntax.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 13:48:26 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/19 16:45:37 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printinsult(t_shell *shell, char s1)
{
	int		random;

	random = ft_gettimems(shell->envp) % 10;
	if (random == 0)
		printf("Syntax Error: Are you drunk? ");
	if (random == 1)
		printf("Syntax Error: Where did you learn how to type? ");
	if (random == 2)
		printf("Syntax Error: Is your keyboard broken? ");
	if (random == 3)
		printf("Syntax Error: Why don't you try a GUI? ");
	if (random == 4)
		printf("Syntax Error: What are you trying to do Yuka? ");
	if (random == 5)
		printf("Syntax Error: This is not a searchbar... ");
	if (random == 6)
		printf("Syntax Error: Monkeys shouldn't use this computer. ");
	if (random == 7)
		printf("Syntax Error: Why don't you go read the manual? ");
	if (random == 8)
		printf("Syntax Error: Even I know ");
	if (random == 9)
		printf("Syntax Error: Shell Licence revoked. ");
	printf("you can't follow up this %c like that\n", s1);
}

int		ft_syntaxerror(t_shell *shell, char s1, char *line, int i)
{
	int		j;
	char	*help;

	ft_printinsult(shell, s1);
	help = ft_calloc(ft_strlen(line), 8);
	j = 0;
	while (j < i)
	{
		help[j] = ' ';
		j++;
	}
	help[j] = '^';
	help[j + 1] = '\0';
	printf("%s\n", line);
	printf("%s\n", help);
	shell->code = 2;
	return (1);
}

int		ft_checksymbol(char *line, int i, char symbol)
{
	int		j;
	j = 1;
	if (line[i + j] == symbol)
		j++;
	while (line[i + j] == ' ')
		j++;
	if (ft_strchr("<>&|", line[i + j]))
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
		if (ft_strchr("<>&|", line[i]))
		{
			if (line[i] == '<')
			{
				t = ft_checksymbol(line, i, '<');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '<', line, i));
			}
			if (line[i] == '>')
			{
				t = ft_checksymbol(line, i, '>');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '>', line, i));
			}
			if (line[i] == '&')
			{
				t = ft_checksymbol(line, i, '&');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '&', line, i));
			}
			if (line[i] == '|')
			{
				t = ft_checksymbol(line, i, '|');
				i = i + t;
				if (!t)
					return (ft_syntaxerror(shell, '|', line, i));
			}
		}
		i++;
	}
	return (0);
}
