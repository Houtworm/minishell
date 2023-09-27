/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 21:31:26 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/26 23:13:13 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//true || (cat -r && cat -z && cat -r && cat -r || false) || echo hallo
// 0, 1, 1, 1, 1, 2, 0
// add $() case, skip
//printf $(echo 'hey
// > hello')

int ft_priority(t_cmds *cmds, int cmdnbr)
{
    int prio;
    int i;
    int k;
    char check;

    i = 0;
    k = 0;
    prio = 0;
    check = '\0';
    while (cmds[cmdnbr].pipeline[i + k])
    {
        while (cmds[cmdnbr].pipeline[i + k] == '(')
        {
            k++;
            prio = 1;
        }
        while (cmds[cmdnbr].pipeline[i + k] == ')')
        {
            k++;
            prio = 2;
        }
        while (cmds[cmdnbr].pipeline[i + k] == '\"' || cmds[cmdnbr].pipeline[i + k] == '\'')
		{
            check = cmds[cmdnbr].pipeline[i + k];
            cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
            i++;
            while (cmds[cmdnbr].pipeline[i + k] && check != cmds[cmdnbr].pipeline[i + k])
            {
                cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
                i++;
            }
            cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
            i++;
        }
        cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
        i++;
    }
    cmds[cmdnbr].pipeline[i + k] = '\0';
    if (cmdnbr > 0 && prio != 2 && cmds[cmdnbr - 1].prio == 1)
        prio = 1;
    return (prio);
}