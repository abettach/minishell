/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:33 by abettach          #+#    #+#             */
/*   Updated: 2021/02/27 16:41:26 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_get_path(t_mini *mini)
{
    int i = 0;
    int j = 0;

    while (mini->envp_g[i][0] != 'P' || mini->envp_g[i][1] != 'A' || mini->envp_g[i][2] != 'T' || mini->envp_g[i][3] != 'H')
        i++;
    while (mini->envp_g[i][j] != '=')
        j++;
    j++;
    mini->path = &mini->envp_g[i][j];
    mini->add_path = ft_split(mini->path, ':');
    i = 0;
    struct stat buffer;
    while (mini->add_path[i])
    {
        mini->add_path[i] = ft_strjoin(mini->add_path[i], "/");
        mini->add_path[i] = ft_strjoin(mini->add_path[i], mini->args[0]);
        i++;
    }
    i = -1;
    while (mini->add_path[++i])
        if (stat(mini->add_path[i], &buffer) == 0)
            mini->run_path = mini->add_path[i];
}

void ft_check_home(t_mini *mini)
{
    int i = 0;
    int j = 0;
    while (ft_strncmp(mini->envp_g[i], "HOME=/", 6) != 0 && mini->envp_g[i + 1])
        i++;
    if (ft_strncmp(mini->envp_g[i], "HOME=", ft_strlen("HOME=")) != 0)
    {
        mini->home_error = (char *)malloc(sizeof(char) * (6));
        mini->home_error = "ERROR\0";
    }
    else
    {
        mini->home_error = (char *)malloc(sizeof(char) * (9));
        mini->home_error = "NO_ERROR\0";
    }
}

void ft_get_home(t_mini *mini)
{
    int i = 0;
    int j = 0;
    while (ft_strncmp(mini->envp_g[i], "HOME=", 5) != 0 && mini->envp_g[i + 1])
        i++;
    if (ft_strncmp(mini->envp_g[i], "HOME=", ft_strlen("HOME=")) == 0)
        mini->home = &mini->envp_g[i][5];
}