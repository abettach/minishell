/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:14 by abettach          #+#    #+#             */
/*   Updated: 2021/02/22 15:21:40 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_redirection(t_mini *mini, int i, char *type)
{
    int j = -1;
    int index;

    mini->STD = 1;
    index = i;
    while ((ft_strcmp(mini->args[i], ">") == 0 || ft_strcmp(mini->args[i], ">>") == 0 || ft_strcmp(mini->args[i], "<") == 0) && mini->args[i])
    {
        type = mini->args[i];
        i++;
        g_input_file = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i]) + 1));
        g_input_file = "";
        g_input_file = ft_strjoin(g_input_file,mini->args[i]);
        if (ft_strcmp(type, ">") == 0)
            mini->redirection_fd = open(g_input_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
        else if (ft_strcmp(type, ">>") == 0)
            mini->redirection_fd = open(g_input_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        else if (ft_strcmp(type, "<") == 0)
        {
            mini->STD = 0;
            mini->redirection_fd = open(g_input_file, O_RDWR, 0777);
        }
        free(g_input_file);
        i++;
    }
    while (mini->args[index])
    {
        mini->args[index] = NULL;
        mini->ArgsNum--;
        index++;
    }
    dup2(mini->redirection_fd, mini->STD);
}

int ft_check_redirection(t_mini *mini)
{
    int i = 0;
    int j = 0;

    mini->redirection = 0;
    while (mini->args[i])
    {
        mini->STD = -1;
        if (ft_strcmp(mini->args[i], ">") == 0 || ft_strcmp(mini->args[i], ">>") == 0 || ft_strcmp(mini->args[i], "<") == 0)
            ft_redirection(mini, i, mini->args[i]);
        i++;
    }

    return 0;
}