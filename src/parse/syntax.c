/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   syntax.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 13:48:26 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/19 15:01:38 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_syntaxerror(t_shell *shell, char s1, char s2)
{
	int		random;

	random = ft_gettimems(shell->envp) % 10;
	if (random == 0)
		printf("Are you drunk? you can't follow %c with %c\n", s1, s2);
	if (random == 1)
		printf("Where did you learn how to type? you can't follow %c with %c\n", s1, s2);
	if (random == 2)
		printf("Is your keyboard broken? you can't follow %c with %c\n", s1, s2);
	if (random == 3)
		printf("Why don't you try a GUI? you can't follow %c with %c\n", s1, s2);
	if (random == 4)
		printf("What are you trying to do Yuka? you can't follow %c with %c\n", s1, s2);
	if (random == 5)
		printf("This is not a searchbar... you can't follow %c with %c\n", s1, s2);
	if (random == 6)
		printf("Monkeys shouldn't use this computer. you can't follow %c with %c\n", s1, s2);
	if (random == 7)
		printf("Why don't you go read the manual? you can't follow %c with %c\n", s1, s2);
	if (random == 8)
		printf("Even I know you can't follow %c with %c\n", s1, s2);
	if (random == 9)
		printf("Shell Licence revoked. you can't follow %c with %c\n", s1, s2);
	shell->code = 2;
	return (1);
}

int		ft_checksymbol(char *line, int i, char symbol)
{
	i++;
	if (line[i] == symbol)
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_strchr("<>&|", line[i]))
		return (0);
	return (i);
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
				if (t)
					i = i + t;
				else
					return (ft_syntaxerror(shell, '<', line[i]));
			}
			if (line[i] == '>')
			{
				t = ft_checksymbol(line, i, '>');
				if (t)
					i = i + t;
				else
					return (ft_syntaxerror(shell, '>', line[i]));
			}
			if (line[i] == '&')
			{
				t = ft_checksymbol(line, i, '&');
				if (t)
					i = i + t;
				else
					return (ft_syntaxerror(shell, '&', line[i]));
			}
			if (line[i] == '|')
			{
				t = ft_checksymbol(line, i, '|');
				if (t)
					i = i + t;
				else
					return (ft_syntaxerror(shell, '|', line[i]));
			}
		}
		i++;
	}
	return (0);
}
