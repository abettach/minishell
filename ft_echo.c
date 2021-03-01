/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:04 by abettach          #+#    #+#             */
/*   Updated: 2021/03/01 16:12:40 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_mini *mini)
{
    int i = 1;
    int j = 0;
    int deja = 0;

    ft_skipe_quotes(mini);
    if ((ft_strcmp(mini->args[1], "-n") == 0 && mini->args[2]) || (ft_strcmp(mini->args[1], "-n") != 0 && mini->args[1]))
    {
        while (mini->args[i])
        {
            j = 0;
            if ((ft_strcmp(mini->args[i], "-n") == 0) && deja == 0)
            {
                while ((ft_strcmp(mini->args[i], "-n") == 0))
                    i++;
                deja = 1;
            }
            ft_putstr(&mini->args[i][j]);
            if (i + 1 < mini->ArgsNum)
                ft_putstr(" ");
            i++;
        }
    }
    if (ft_strcmp(mini->args[1], "-n") != 0 && mini->redirection_nocommand == 0)
        ft_putstr("\n");
}