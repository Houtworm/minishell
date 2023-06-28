/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_test.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/06/28 19:19:05 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//example commandline 
// cat < file1 | grep a | wc -l > file2 > file3 ; echo "hello; world | hey" | grep e; echo b

//  cat < file1 | grep a | wc -l > file2 > file3 ; 
//  echo "hello; world | hey" | grep e;
//  echo b
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (c == *s)
			return ((char *)s);
		s++;
	}
	if (c == *s)
		return ((char *)s);
	return (0);
}

//skip double quote and count str to be malloced
static int	count_str_skip(char *s, int c, int z)
{
	int	str_count;
	int	skip;
	int	i;

	str_count = 0;
	i = 0;
	skip = 0;
    while (s[i] && s[i] == c)
		    ++i;
	while (s[i])
	{
		while (s[i] && s[i] != c)
		{
			if (s[i] == z && ft_strchr(s + i, z))
            {
				s = ft_strchr(s + i + 1, z);
                i = 1;
            }
			++i;
		}
		++str_count;
	    while (s[i] && s[i] == c)
		    ++i;
	}
	return (str_count);
}

int    main(void)
{
    char    *s = "hey; \"hello; world\"ads";
    printf("%d\n", count_str_skip(s, ';', '"'));
}

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	char	**arr;

// 	i = 0;
// 	arr = ft_calloc(count_str_skip(s, c, '"') + 1, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (s[i] == c)
// 		++i;
// 	arr = loop(s, c, i, arr);
// 	if (!arr)
// 		return (NULL);
// 	return (arr);
// }

// char	**ft_split_skip(char const *s, char c)
// {
// 	char	**r;
// 	int		iw;

// 	if (!s)
// 		return (NULL);
// 	iw = 0;
// 	r = ft_calloc(sizeof(r) * (ft_cntwrd((char *)s, c) + 1), 1);
// 	if (!r)
// 		return (NULL);
// 	while (ft_cntwrd((char *)s, c) > 0)
// 	{
// 		while (*s == c)
// 			s++;
// 		r[iw] = ft_malstr((char *)s, c);
// 		if (r[iw] == NULL)
// 			return (ft_frenarr(r, iw));
// 		while (*s != c && *s != '\0')
// 			s++;
// 		iw++;
// 	}
// 	return (r);
// }


