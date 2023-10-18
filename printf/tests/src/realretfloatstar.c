/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   realretfloatstar.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:19:04 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	return (printf(argv[1], atoi(argv[2]), atof(argv[3])));
}
