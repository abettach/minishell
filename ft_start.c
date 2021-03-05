/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:49 by abettach          #+#    #+#             */
/*   Updated: 2021/03/05 17:41:57 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sorte_args(t_mini *mini)
{
    int i = 0;
    int j = 2;

    if ((ft_strcmp(mini->args[0], ">") == 0 || ft_strcmp(mini->args[0], ">>") == 0 || ft_strcmp(mini->args[0], "<") == 0) && mini->args[2])
    {
        mini->sort_args = malloc(sizeof(char *) * (mini->ArgsNum + 1));
        while (mini->args[j])
        {
            mini->sort_args[i] = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[j] + 1)));
            mini->sort_args[i] = ft_strcpy(mini->sort_args[i], mini->args[j]);
            j++;
            i++;
        }
        j = 0;
        while (mini->args[j] && j < 2)
        {
            mini->sort_args[i] = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[j] + 1)));
            mini->sort_args[i] = ft_strcpy(mini->sort_args[i], mini->args[j]);
            j++;
            i++;
        }
        mini->sort_args[i] = NULL;
        // i = -1;
        // if (mini->args)
        //     free(mini->args);
        // while (mini->args[++i])
        //     free(mini->args[i]);
        // i = 0;
        // while (mini->sort_args[i])
        //     i++;
        // mini->args = malloc(sizeof(char *) * i);
        // i = 0;
        // while (mini->sort_args[i])
        // {
        //     mini->args[i] = (char *)malloc(sizeof(char *) * (ft_strlen(mini->sort_args[i])));
        //     mini->args[i] = ft_strcpy(mini->args[i])
        // }
        mini->args = mini->sort_args;
    }
}

int ft_sp_char(char c)
{
    if (c == '$' || c == '"' || c == '\\' || c == '`')
        return 1;
    return 0;
}
void ft_quotes_one(t_mini *mini, int i)
{
    int j = 0;
    int inside_quotes = 0;
    int count = 0;
    char *arg;

    arg = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i]) - 2));
    while (mini->args[i][j])
    {
        if (mini->args[i][j] == 34)
        {
            inside_quotes = 1;
            j++;
        }
        if (mini->args[i][j] == 92 && ft_sp_char(mini->args[i][j + 1]) == 1)
        {
            j++;
        }
        if (mini->args[i][j] == 34 && inside_quotes == 1 && mini->args[i][j - 1] != 92)
        {
            inside_quotes = 0;
            j++;
        }
        arg[count] = mini->args[i][j];
        j++;
        count++;
    }
    arg[count] = '\0';
    free(mini->args[i]);
    mini->args[i] = (char *)malloc(sizeof(char) * (count));
    mini->args[i] = ft_strcpy(mini->args[i], arg);
    free(arg);
}

void ft_quotes_two(t_mini *mini, int i)
{
    int j = 0;
    int inside_quotes = 0;
    int count = 0;
    char *arg;

    puts("here");
    arg = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i]) - 2));
    while (mini->args[i][j])
    {
        if (mini->args[i][j] == 92 && mini->args[i][j + 1] == 39)
            j++;
        if (mini->args[i][j] == 39 && mini->args[i][j-1] != 92)
        {
            inside_quotes = 1;
            j++;
        }
        if (mini->args[i][j] == 39 && inside_quotes == 1 && mini->args[i][j - 1] != 92)
        {
            inside_quotes = 0;
            j++;
        }
        arg[count] = mini->args[i][j];
        j++;
        count++;
    }
    arg[count] = '\0';
    mini->args[i] = arg;
}

int ft_92(char *arg)
{
    int i = 0;
    while (arg[i])
    {
        if (arg[i] == 92)
            return 1;
        i++;
    }
    return 0;
}
int     quotes_closed(char *arg, char type)
{
    int i = 0;
    while (arg[i])
    {
        if (arg[i] == type)
            return 1;
        i++;
    }
    return 0;
}

void    ft_no_92(t_mini *mini, int i)
{
    int j = 0;
    char *arg;
    int count = 0;
    int inside_quotes = 0;

    arg = (char *)malloc(sizeof(char *) * (ft_strlen(mini->args[i])));
    while (mini->args[i][j])
    {
        if (mini->args[i][j] == 92 && inside_quotes == 0)
            j++;
        if ((mini->args[i][j] == 34 && quotes_closed(&mini->args[i][j+1],34) == 1) || (mini->args[i][j] == 39 && quotes_closed(&mini->args[i][j+1],39) == 1))
        {
            j++;
            inside_quotes = 1;
        }
        else if ((((mini->args[i][j] == 34 && quotes_closed(&mini->args[i][j+1],34) == 0) || (mini->args[i][j] == 39 && quotes_closed(&mini->args[i][j+1],39) == 0))
        && (inside_quotes == 1)))
        {
            j++;
            inside_quotes = 0;
        }
        arg[count] = mini->args[i][j];
        count++;
        j++;
    }
    arg[count] = '\0';
    mini->args[i] = arg;
}

void ft_quotes(t_mini *mini)
{
    int i = 0;
    int j = 0;

    while (mini->args[i])
    {
        j = 0;
        while (mini->args[i][j])
        {
            if (mini->args[i][j] == '"' && quotes_closed(&mini->args[i][j+1],'"') == 1)
            {
                ft_quotes_one(mini, i);
                break;
            }
            if (mini->args[i][j] == 39 && quotes_closed(&mini->args[i][j+1],39) == 1)
            {
                ft_quotes_two(mini, i);
                break;
            }
            if ((!mini->args[i][j + 1] && ft_92(mini->args[i]) == 1) || quotes_closed(&mini->args[i][j+1],39) == 0 || quotes_closed(&mini->args[i][j+1],34) == 0)
            {
                ft_no_92(mini, i);
                    break;
            }
            j++;
        }
        i++;
    }
}
void ft_start_minishell(t_mini *mini)
{
    int i = 0;
    pid_t pid;
    int fdd;
    int fd[2];

    pipe(fd);
    while (mini->multi_command[i] != NULL)
    {
        mini->check_pipe = 0;
        ft_check_pipe_command(mini, i);
        mini->line = ft_strcpy(mini->line, mini->multi_command[i]);
        ft_init(mini);
        if (mini->check_pipe == 0)
        {
            ft_get_args(mini);
            ft_quotes(mini);
            ft_dollar(mini);
            ft_sorte_args(mini);
            ft_check_args(mini);
            ft_get_path(mini);
            ft_check_redirection(mini);
        }
        ft_check_home(mini);
        ft_run_command(mini);
        ft_check_home(mini);
        ft_dup2(mini);
        ft_init_pipe(mini);
        mini->home_two = NULL;
        i++;
    }
}
