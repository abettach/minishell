/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:20 by abettach          #+#    #+#             */
/*   Updated: 2021/02/22 15:57:51 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_copy_env(t_mini *mini, char **envp)
{
    int line = 0;
    int i = -1;
    char **tab;

    while (envp[line])
        line++;
    tab = malloc(sizeof(char *) * (line + 1));
    while (envp[++i])
    {
        tab[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i] + 1)));
        tab[i] = ft_strcpy(tab[i], envp[i]);
    }
    return tab;
}

char **ft_copy_export(t_mini *mini, char **envp)
{
    int line = 0;
    int i = -1;
    int k = 0;
    int j = -1;
    char **tab;

    while (mini->envp_g[line])
        line++;
    tab = malloc(sizeof(char *) * (line + 1));
    while (mini->envp_g[++i])
    {
        tab[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i] + 3)));
        j = -1;
        k = 0;
        while (mini->envp_g[i][++j])
        {
            if (mini->envp_g[i][j - 1] == '=')
            {
                tab[i][k] = '"';
                k++;
            }
            tab[i][k] = mini->envp_g[i][j];
            k++;
        }
        tab[i][k] = '"';
        tab[i][++k] = '\0';
    }
    return tab;
}

void ft_sort_table(t_mini *mini)
{
    int i = 0;
    char *tmp;

    while (mini->export.tab[i + 1] != NULL)
    {
        if (ft_strcmp(mini->export.tab[i], mini->export.tab[i + 1]) > 0)
        {
            tmp = mini->export.tab[i];
            mini->export.tab[i] = mini->export.tab[i + 1];
            mini->export.tab[i + 1] = tmp;
            i = 0;
        }
        else if (ft_strcmp(mini->export.tab[i], mini->export.tab[i + 1]) <= 0)
            i++;
    }
    i = 0;
    while (mini->export.tab[i])
    {
        ft_putstr("declare -x ");
        ft_putstr(mini->export.tab[i]);
        ft_putstr("\n");
        i++;
    }
}

int     ft_check_quotes(t_mini *mini)
{
    int i = 0;
    int j = 0;
    while (mini->args[i])
    {
        j = 0;
        while(mini->args[i][j])
        {
            if (mini->args[i][j] == '"' || mini->args[i][j] == 39)
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}
void ft_skipe_quotes(t_mini *mini)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **new_tab;

    if (ft_check_quotes(mini) == 1)
    {
        new_tab = malloc(sizeof(char *) * (mini->ArgsNum + 1));
        while (mini->args[i])
        {
            new_tab[i] = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[i]) + 1));
            k = 0;
            j = 0;
            while (mini->args[i][j])
            {
                if (mini->args[i][j] == 34 || mini->args[i][j] == '\'')
                    j++;
                new_tab[i][k] = mini->args[i][j];
                k++;
                j++;
            }
            i++;
        }
        mini->args = new_tab;
    }
}
void ft_export(t_mini *mini)
{
    int i = 1;
    int j = 0;
    int l = -1;
    char *arg;

    if (mini->args[i][0] == 34)
        ft_skipe_quotes(mini);
    if (mini->ArgsNum > 1)
    {
        if ((mini->args[i][0] >= 'a' && mini->args[i][0] <= 'z') ||
            (mini->args[i][0] >= 'A' && mini->args[i][0] <= 'Z') || (mini->args[i][0] == '_'))
        {
            if (ft_equal_check(mini, mini->args[i]) == 1 && mini->args[i][0] != '_')
                while (i < mini->ArgsNum)
                {
                    j = 0;
                    while (mini->args[i][j] != '=')
                        j++;
                    arg = (char *)malloc(sizeof(char) * (j + 2)); // 2 3la wed bash ta '=' t7ssb
                    ft_strlcpy(arg, mini->args[i], j);            ////// strlcopy traaaaaaaaaaaash (+1 size idk)
                    j = -1;
                    while (mini->envp_g[++j])
                        if (ft_strncmp(mini->envp_g[j], arg, ft_strlen(arg)) == 0)
                            mini->envp_g = ft_remove_unset(mini, j);
                    ft_strjoin2(mini->envp_g, mini->args[i]);
                    i++;
                }
        }
        else
            ft_error("bash: export: ", mini->args[i], ": not a valid identifier\n");
    }
    if (mini->ArgsNum == 1)
    {
        mini->export.tab = ft_copy_export(mini, mini->envp_g);
        ft_sort_table(mini);
    }
}