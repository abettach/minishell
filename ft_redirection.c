/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:14 by abettach          #+#    #+#             */
/*   Updated: 2021/03/01 15:51:27 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cat_redirection(t_mini *mini)
{
    char **tmp;
    int i = 0;
    int j = 0;

    tmp = malloc(sizeof(char *) * 3);
    while (mini->args[i])
    {
        if (ft_strcmp(mini->args[i], "<") == 0)
            i++;
        tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i])));
        tmp[j] = "";
        tmp[j] = ft_strjoin(tmp[j], mini->args[i]);
        i++;
        j++;
    }
    tmp[j] = NULL;
    mini->args = tmp;
}

void ft_redirection(t_mini *mini, int i, char *type)
{
    int index;

    mini->redirection = 1;
    index = i;
    while ((ft_strcmp(mini->args[i], ">") == 0 || ft_strcmp(mini->args[i], ">>") == 0 || ft_strcmp(mini->args[i], "<") == 0) && mini->args[i])
    {
        type = mini->args[i];
        i++;
        g_input_file = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i]) + 1));
        g_input_file = "";
        g_input_file = ft_strjoin(g_input_file, mini->args[i]);
        if (ft_strcmp(type, ">") == 0)
        {
            mini->STD = 1;
            mini->redirection_fd = open(g_input_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
        }
        else if (ft_strcmp(type, ">>") == 0)
        {
            mini->STD = 1;
            mini->redirection_fd = open(g_input_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        }
        else if (ft_strcmp(type, "<") == 0)
        {
            mini->STD = 0;
            mini->redirection = 0;
            mini->redirection_fd = open(g_input_file, O_RDWR, 0777);
        }
        free(g_input_file);
        i++;
    }
    if (ft_strcmp(mini->args[0], "cat") == 0 && ft_strcmp(type, "<") == 0)
    {
        mini->redirection = 0;
        ft_cat_redirection(mini);
    }
    else
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
    ft_redirection_nocommand(mini);
    while (mini->args[i])
    {
        mini->STD = -1;
        if (ft_strcmp(mini->args[i], ">") == 0 || ft_strcmp(mini->args[i], ">>") == 0 || ft_strcmp(mini->args[i], "<") == 0)
            ft_redirection(mini, i, mini->args[i]);
        i++;
    }

    return 0;
}