/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:02 by abettach          #+#    #+#             */
/*   Updated: 2021/03/01 15:52:30 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_pipe(t_mini *mini)
{
    int i = 0;

    if (mini->pipe.args[i])
    {
        mini->pipe.args[i] = NULL;
        free(mini->pipe.args[i]);
        i++;
    }
}
//test
void ft_get_pipe_args(t_mini *mini, int k)
{
    int i = -1;
    int arg = -1;
    int carg = 0;
    mini->args = ft_split(mini->pipe.args[k], ' ');
    while (mini->args[++i])
        ;
    mini->ArgsNum = i;
}

int ft_check_pipe(t_mini *mini, char **envp, int i)
{
    int j = 0;
    while (mini->multi_command[i][j])
    {
        if (mini->multi_command[i][j] == '|')
            return 1;
        j++;
    }
    return 0;
}

void ft_remove_pipe_space(t_mini *mini, int i)
{
    int j = 0;
    int k = 0;
    int spaces = 0;
    char tmp;
    char *str;

    while (mini->multi_command[i][j])
    {
        if (mini->multi_command[i][j] == ' ')
            spaces++;
        j++;
    }
    j -= spaces;
    str = (char *)malloc(sizeof(char) * (j + 1));
    j = 0;
    while (mini->multi_command[i][j])
    {
        if ((mini->multi_command[i][j] == ' ' && mini->multi_command[i][j + 1] == '|') || (mini->multi_command[i][j] == ' ' && mini->multi_command[i][j - 1] == '|'))
            j++;
        str[k] = mini->multi_command[i][j];
        k++;
        j++;
    }
    str[k] = '\0';
    mini->multi_command[i] = NULL;
    mini->multi_command[i] = str;
    free(str);
}

void ft_pipe(t_mini *mini, int i)
{
    ft_remove_pipe_space(mini, i);
    mini->pipe.args = ft_split(mini->multi_command[i], '|');
}

void ft_pipe_run(t_mini *mini)
{
    int fd[2];
    pid_t pid;
    char *command;
    int status;
    int i = 0;
    int fdd = 0;

    while (mini->pipe.args[i] != NULL)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            dup2(fdd, 0);
            ft_init(mini);
            ft_get_pipe_args(mini, i);
            ft_dollar(mini);
            ft_sorte_args(mini);
            ft_check_args(mini);
            ft_get_path(mini);
            ft_check_redirection(mini);
            command = mini->args[0][0] == '/' ? mini->args[0] : mini->run_path;
            if (mini->pipe.args[i + 1] && mini->redirection == 0)
                dup2(fd[1], 1);
            ft_command_2(mini, command);
            close(fd[0]);
            exit(1);
        }
        else
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                mini->exit_status = WEXITSTATUS(status);
            close(fd[1]);
            fdd = fd[0];
        }
        i++;
    }
}

void ft_check_pipe_command(t_mini *mini, int i)
{
    int j = 0;
    while (mini->multi_command[i][j])
    {
        if (mini->multi_command[i][j] == '|')
        {
            mini->check_pipe = 1;
            ft_pipe(mini, i);
            return;
        }
        j++;
    }
    mini->check_pipe = 0;
    mini->pipe.args = malloc(sizeof(char *) * 2);
    mini->pipe.args[0] = (char *)malloc(sizeof(char) * (ft_strlen(mini->multi_command[i]) + 1));
    mini->pipe.args[0] = ft_strcpy(mini->pipe.args[0], mini->multi_command[i]);
    mini->pipe.args[1] = NULL;
}