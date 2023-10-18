/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insults.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 19:42:14 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:04 by houtworm      ########   odam.nl         */
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
	insults[10] = ft_strdup("You do that again and see what happens... ");
	insults[11] = ft_strdup("Why don't you go back to your Mac? ");
	insults[12] = ft_strdup("You know Cocaine is bad for you right? ");
	insults[13] = ft_strdup("Your syntax illiteracy makes me a sad shell... ");
	insults[14] = ft_strdup("Everytime you do this someone gets killed ");
	insults[15] = ft_strdup("Mi Inglash us coparible toe yoer sienthax ");
	insults[16] = ft_strdup("RTFM https://gnu.org/software/bash/manual ");
	insults[17] = ft_strdup("This incident will be reported. ");
	insults[18] = ft_strdup("I think a tamagotchi is better suited for you. ");
	insults[19] = ft_strdup("You are just wasting your time... ");
	return (insults);
}

void	ft_printinsult(t_shell *msh)
{
	char	**insults;
	int		random;

	insults = ft_getinsults();
	random = ft_gettimemsdate(msh->envp) % 20;
	ft_putendl_fd(insults[random], 2);
	ft_frearr(insults);
}

