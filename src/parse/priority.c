/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 21:31:26 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/03 23:22:19 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_priority(t_cmds *cmds, int cmdnbr)
{
    int prio;
    int i;
    int k;

    i = 0;
    k = 0;
    prio = 0;
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
        while (cmds[cmdnbr].pipeline[i + k] == '$')
        {
            while (cmds[cmdnbr].pipeline[i + k] && cmds[cmdnbr].pipeline[i + k] != ')')
            {
                while (cmds[cmdnbr].pipeline[i + k] == '\"' || cmds[cmdnbr].pipeline[i + k] == '\'')
                {
                    ft_copyquote(&(cmds[cmdnbr].pipeline), cmds[cmdnbr].pipeline, i, i + k);
                    i = ft_skipquote(cmds[cmdnbr].pipeline, i + k) + 1;
                }
                cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
                i++;
            }
        }
        while (cmds[cmdnbr].pipeline[i + k] == '\"' || cmds[cmdnbr].pipeline[i + k] == '\'')
		{
            ft_copyquote(&(cmds[cmdnbr].pipeline), cmds[cmdnbr].pipeline, i, i + k);
            i = ft_skipquote(cmds[cmdnbr].pipeline, i + k) + 1;
        }
        cmds[cmdnbr].pipeline[i] = cmds[cmdnbr].pipeline[i + k];
        i++;
    }
    cmds[cmdnbr].pipeline[i + k] = '\0';
    if (cmdnbr > 0 && prio != 2 && cmds[cmdnbr - 1].prio)
        prio = 1;
    return (prio);
}