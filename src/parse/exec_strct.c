/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_strct.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 17:38:38 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/24 23:36:28 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

OK!
bash-3.2$ ls && echo 'hello'
bash-3.2$ ls &&echo 'hello'
bash-3.2$ ls&&echo 'hello'

BAD :(
bash-3.2$ ls&&&echo 'hello'
bash: syntax error near unexpected token `&'
bash-3.2$ ls&& &echo 'hello'
bash: syntax error near unexpected token `&'
bash-3.2$ ls&&;echo 'hello'
bash: syntax error near unexpected token `;'
bash-3.2$ ls&& ;echo 'hello'
bash: syntax error near unexpected token `;'

Danny here, I added these lines to the tester, feel free to add any edge cases you can think off so we can see if we accidently break it again :)
I also don't mind if you comment out parts of the tester for some clarity :), it is easier if you just see the tests you are working on :)
*/


int	symbol_check(char	*s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '&' || s[i] != '|' || s[i] != ';')
		return (i + 1);
	return (0); //ft_error(ex. bash: +echo: command not found)
}

int	count_str2(char *s)
{
	int	str_count;
	int	i;
	int	j;

	str_count = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\"' || (s[i] == '\''))
		{
			j++;
			while (s[i + j] != s[i])
				j++;
		}
		i = i + j;
		if ((s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '|' && s[i + 1] == '|'))
			i += symbol_check(s + i + 2);
		if (s[i] == '&' || s[i] == ';')
			i += symbol_check(s + i + 1);
		str_count++;
		i++;
	}
	return (str_count + 1);
}
