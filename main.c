/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:19:07 by abettach          #+#    #+#             */
/*   Updated: 2021/02/25 16:57:49 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_style(t_mini *mini)
{
    ft_putstr(GRN);
    ft_putstr("➜  ");
    ft_putstr(RED);
    ft_putstr("minishell");
    ft_putstr(WHT);
    ft_putstr("$ ");
}

void ft_redirection_space(t_mini *mini)
{
    char *new_line;
    int i = 0, j = 0;
    int space_nb = 0;
    int redirection_type;
    int index;

    while (mini->line[i])
    {
        if (mini->line[i] == '>' && mini->line[i + 1] != '>')
        {
            redirection_type = 1;
            if (mini->line[i - 1] != ' ')
                space_nb++;
            if (mini->line[i + 1] != ' ')
                space_nb++;
        }
        else if (mini->line[i] == '<')
        {
            redirection_type = 2;
            if (mini->line[i - 1] != ' ')
                space_nb++;
            if (mini->line[i + 1] != ' ')
                space_nb++;
        }
        else if (mini->line[i] == '>' && mini->line[i + 1] == '>')
        {
            redirection_type = 3;
            if (mini->line[i - 1] != ' ')
                space_nb++;
            if (mini->line[i + 2] != ' ')
                space_nb++;
        }
        i++;
    }
    i = 0;
    j = 0;
    new_line = (char *)malloc(sizeof(char) * (ft_strlen(mini->line) + space_nb + 1));
    while (mini->line[i])
    {
        if (mini->line[i] == '>' && mini->line[i + 1] != '>' && mini->line[i - 1] != '>')
        {
            if (mini->line[i - 1] != ' ')
            {
                new_line[j] = ' ';
                j++;
            }
            if (mini->line[i + 1] != ' ')
            {
                new_line[j] = mini->line[i];
                j++;
                new_line[j] = ' ';
                i++;
                j++;
            }
        }
        else if (mini->line[i] == '<')
        {
            if (mini->line[i - 1] != ' ')
            {
                new_line[j] = ' ';
                j++;
            }
            if (mini->line[i + 1] != ' ')
            {
                new_line[j] = mini->line[i];
                j++;
                new_line[j] = ' ';
                i++;
                j++;
            }
        }
        else if (mini->line[i] == '>' && mini->line[i + 1] == '>')
        {
            if (mini->line[i - 1] != ' ')
            {
                new_line[j] = ' ';
                j++;
            }
        }
        else if (mini->line[i - 1] == '>' && mini->line[i - 2] == '>')
        {
            if (mini->line[i] != ' ')
            {
                new_line[j] = ' ';
                j++;
            }
        }
        new_line[j] = mini->line[i];
        i++;
        j++;
    }
    new_line[j] = '\0';
    mini->line = new_line;
}

void ft_redirection_nocommand(t_mini *mini)
{
    char **new_args;
    int i = 0;
    int j = 0;

    mini->redirection_nocommand = 0;
    if (ft_strcmp(mini->args[0], ">") == 0 || ft_strcmp(mini->args[0], ">>") == 0)
    {
        mini->redirection_nocommand = 1;
        new_args = malloc(sizeof(char *) * (5));
        new_args[i] = (char *)malloc(sizeof(char) * (5));
        new_args[i] = "";
        new_args[i] = ft_strjoin(new_args[i], "echo");
        i++;
        new_args[i] = (char *)malloc(sizeof(char) * (2));
        new_args[i] = ft_strcpy(new_args[i], "-n");
        i++;
        while (mini->args[j])
        {
            new_args[i] = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[j]) + 1));
            new_args[i] = ft_strcpy(new_args[i], mini->args[j]);
            i++;
            j++;
        }
        new_args[i] = NULL;
        mini->args = new_args;
    }
}

char *ft_skipe_quotes_str(t_mini *mini)
{
    int i = 0;
    int index = 0;
    int j = 0;
    char *new_line;

    while (mini->line[i])
    {
        if (mini->line[i] == 34)
            index++;
        i++;
    }
    i = 0;
    new_line = (char *)malloc(sizeof(char) * (ft_strlen(mini->line) - index) + 1);
    while (mini->line[i])
    {
        while (mini->line[i] == 34)
            i++;
        new_line[j] = mini->line[i];
        i++;
        j++;
    }
    new_line[j] = '\0';
    return new_line;
}

int main(int argc, char **argv, char **envp)
{
    t_mini mini;
    int i = 0;
    int r;

    //printf("\n\n\t\tMINISHELL\t\t\n\n");
    // mini.exit_status = 0;
    getcwd(mini.cwd, sizeof(mini.cwd));
    mini.envp_g = ft_copy_env(&mini, envp);
    ft_get_home(&mini);
    mini.first_lvl = ft_atoi(ft_env_shellvl(&mini));
    mini.shell_lvl = mini.first_lvl;
    mini.first_lvl++;
    ft_shell_lvl(&mini);
    while (1)
    {
        getcwd(mini.cwd, sizeof(mini.cwd));
        g_cwd = mini.cwd;
        // ft_style(&mini);
        signal(SIGINT, ft_ctrl_c);
        signal(SIGQUIT, ft_ctrl_anti);
        r = get_next_line(0, &mini.line, &mini);
        mini.line = ft_skipe_quotes_str(&mini);
        if (r == 0)
        {
            ft_putstr("exit\n");
            exit(0);
        }
        while (*mini.line == ' ' || *mini.line == '\t')
            mini.line++;
        if (mini.line[0] != '\0' && mini.line[0] != ' ')
        {
            ft_init(&mini);
            if ((syn_error(&mini) == 0))
            {
                ft_redirection_space(&mini);
                ft_check_multi_command(&mini);
                ft_start_minishell(&mini);
                ft_free_all(&mini);
            }
        }
    }
    return (0);
}