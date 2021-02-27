/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:16:29 by abettach          #+#    #+#             */
/*   Updated: 2021/02/27 16:36:38 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_old_pwd(t_mini *mini)
{
    int i = -1;
    mini->OLDPWD = (char *)malloc(sizeof(char) * (ft_strlen(mini->cwd) + 8));
    mini->OLDPWD = ft_strjoin("OLDPWD=", mini->cwd);
    while (mini->envp_g[++i])
        if (ft_strncmp(mini->envp_g[i], "OLDPWD=", 7) == 0)
            mini->envp_g = ft_remove_unset(mini, i);
    ft_strjoin2(mini->envp_g, mini->OLDPWD);
    free(mini->OLDPWD);
}

void ft_cd(t_mini *mini)
{
    ft_old_pwd(mini);
    if (mini->args[1] == NULL)
    {
        if (ft_strcmp(mini->home_error, "ERROR\0") == 0)
        {
            ft_error("cd: HOME not set", "", "\n");
            return;
        }
        mini->args[1] = mini->home;
    }
    chdir(mini->args[1]);
}