/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:16:41 by abettach          #+#    #+#             */
/*   Updated: 2021/03/04 15:37:46 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_env_shellvl(t_mini *mini)
{
    int i = 0, j = 0;
    while (mini->envp_g[i])
    {
        if (ft_strncmp(mini->envp_g[i], "SHLVL=", 6) == 0)
        {
            while (mini->envp_g[i][j] != '=')
                j++;
            j++;
            return &mini->envp_g[i][j];
        }
        i++;
    }
    return NULL;
}

void ft_shell_lvl(t_mini *mini)
{
    char *arg;
    int j = -1;

    arg = "SHLVL=";
    while (mini->envp_g[++j])
        if (ft_strncmp(mini->envp_g[j], arg, ft_strlen(arg)) == 0)
            mini->envp_g = ft_remove_unset(mini, j);
    
    mini->shell_lvl++;
    arg = ft_strjoin(arg, ft_itoa(mini->shell_lvl));
    ft_strjoin2(mini->envp_g, arg);
}

void ft_exec(t_mini *mini, char *command)
{
    pid_t pid;
    int status = 0;
    pid = fork();
    if (pid == 0)
        execve(command, mini->args, mini->envp_g);
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            mini->exit_status = WEXITSTATUS(status);
    }
}

void ft_command_2(t_mini *mini, char *command)
{
    if (ft_strcmp(mini->args[0], TYPE_CD) == 0)
        ft_cd(mini);
    else if (ft_strcmp(mini->args[0], TYPE_PWD) == 0)
        ft_pwd(mini);
    else if (ft_strcmp(mini->args[0], TYPE_ECHO) == 0)
        ft_echo(mini);
    else if (ft_strcmp(mini->args[0], TYPE_ENV) == 0)
        ft_env(mini);
    else if (ft_strcmp(mini->args[0], TYPE_EXPORT) == 0)
        ft_export(mini);
    else if (ft_strcmp(mini->args[0], TYPE_UNSET) == 0)
        ft_unset(mini);
    else if (ft_strcmp(mini->args[0], TYPE_EXITE) == 0)
        ft_exit(mini);
    else if (mini->run_path == NULL && mini->args[0][0] != '/' && mini->args[0][0] != '$'
    && ft_strcmp(mini->args[0],"./minishell") != 0 && ft_strcmp(mini->args[0], "minishell") != 0)
    {
        mini->exit_status = 127;
        ft_error(mini->args[0], ": command not found", "\n");
    }
    else
        ft_exec(mini, command);
}

void ft_run_command(t_mini *mini)
{
    char *command;
    pid_t pid = 0;
    int status = 0;

    if (mini->check_pipe == 0)
        command = mini->args[0][0] == '/' ? mini->args[0] : mini->run_path;
    if (command == NULL && mini->check_pipe == 0)
        command = mini->args[0];
    if (mini->check_pipe == 1)
        ft_pipe_run(mini);
    else
        ft_command_2(mini, command);

    command = NULL;
}