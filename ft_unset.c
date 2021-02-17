/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:57 by abettach          #+#    #+#             */
/*   Updated: 2021/02/08 15:03:09 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_remove_unset(t_mini *mini, int index)
{
    int line = 0;
    int i = -1;
    int j = 0;
    char **tab;

    while (mini->envp_g[line])
        line++;
    tab = malloc(sizeof(char *) * (line + 1));
    while (mini->envp_g[++i])
        if (i != index)
        {
            tab[j] = (char *)malloc(sizeof(char) * (ft_strlen(mini->envp_g[i] + 1)));
            tab[j] = ft_strcpy(tab[j], mini->envp_g[i]);
            j++;
        }
    i = -1;
    while (mini->envp_g[++i])
        mini->envp_g[i] = NULL;
    i = -1;
    while (tab[++i])
    {
        mini->envp_g[i] = (char *)malloc(sizeof(char) * (ft_strlen(tab[i] + 1)));
        mini->envp_g[i] = ft_strcpy(mini->envp_g[i], tab[i]);
    }
    return tab;
}

void ft_unset(t_mini *mini)
{
    char *arg;
    int i;
    int j = 1;
    if (mini->ArgsNum > 1)
        while (j < mini->ArgsNum)
        {
            if ((ft_equal_check(mini, mini->args[j])) == 0)
            {
                arg = ft_strjoin(mini->args[j], "=");
                i = -1;
                while (mini->envp_g[++i])
                    if (ft_strncmp(mini->envp_g[i], arg, ft_strlen(arg)) == 0)
                        mini->envp_g = ft_remove_unset(mini, i);
                j++;
            }
            else
            {
                ft_putstr("unset: ");
                ft_putstr(mini->args[j]);
                ft_putstr(": invalid parameter name\n");
                break;
            }
        }
}