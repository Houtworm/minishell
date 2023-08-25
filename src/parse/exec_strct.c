/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_strct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 17:38:38 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/25 20:41:49 by yitoh         ########   odam.nl         */
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
	if (s[i] != '&' && s[i] != '|' && s[i] != ';')
		return (i + 1);
	ft_errorexit("syntax error near unexpected token", "special character", 258);
	return (0);
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
		i += j;
		if ((s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '|' && s[i + 1] == '|'))
		{
			str_count++;
			i += symbol_check(s + i + 2);
		}
		else if (s[i] == '&' || s[i] == ';')
		{
			str_count++;
			i += symbol_check(s + i + 1);
		}
		i++;
	}
	return (str_count + 1);
}


int	count_wd2(char *s)
{
	int	i;
	int	j;

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
		if (s[i] == '&' || s[i] == '|' || s[i] == ';')
			break ;
		i++;
	}
	return (i);
}

char	**split_spchr(char *s)
{
	int		i;
	int		start;
	char	**cmd;

	i = 0;
	start = 0;
	cmd = ft_calloc(count_str2(s) + 1, sizeof(char *));
	if (!cmd)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (s[start])
	{
		printf("start = %d, %d char\n", start, count_wd2(s + start));
		cmd[i] = ft_substr(s, start, count_wd2(s + start));
		if (!cmd[i])
			return (ft_frenarr(cmd, i));
		start += count_wd2(s + start);
		if ((s[start] == '&' && s[start + 1] == '&')
			|| (s[start] == '|' && s[start + 1] == '|'))
			start ++;
		start++;
		i++;
	}
	return (cmd);
}
