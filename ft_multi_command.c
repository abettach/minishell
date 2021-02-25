/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:51 by abettach          #+#    #+#             */
/*   Updated: 2021/02/25 16:40:42 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_remove_space(t_mini *mini)
{
    int i = 0;
    int j = 0;
    int spaces = 0;
    char tmp;
    char *str;

    while (mini->line[i])
    {
        if (mini->line[i] == ' ')
            spaces++;
        i++;
    }
    i -= spaces;
    str = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (mini->line[i])
    {
        if ((mini->line[i] == ' ' && mini->line[i + 1] == ';') || (mini->line[i] == ' ' && mini->line[i - 1] == ';'))
            i++;
        str[j] = mini->line[i];
        j++;

        i++;
    }
    str[j] = '\0';
    mini->line = NULL;
    mini->line = str;
}
void ft_multi_command(t_mini *mini)
{
    ft_remove_space(mini);
    mini->multi_command = ft_split(mini->line, ';');
}
void ft_check_multi_command(t_mini *mini)
{
    int i = 0;
    int j = 0;
    int index = 0;
    while (mini->line[i])
    {
        if (mini->line[i] == ';')
        {
            index = 1;
            ft_multi_command(mini);
            break;
        }
        i++;
    }
    if (index == 0)
    {
        i = 0;
        mini->multi_command = malloc(sizeof(char *) * 2);
        mini->multi_command[0] = (char *)malloc(sizeof(char) * (ft_strlen(mini->line) + 1));
        while (mini->line[i])
        {
            mini->multi_command[0][j] = mini->line[i];
            i++;
            j++;
        }
        mini->multi_command[0][j] = '\0';
        mini->multi_command[1] = NULL;
    }
}