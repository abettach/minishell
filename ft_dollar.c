/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:16:48 by abettach          #+#    #+#             */
/*   Updated: 2021/03/01 16:25:21 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env_dollar(t_mini *mini, int i)
{
    int k;
    int j;
    char *arg;
    k = -1;
    j = 0;

    arg = ft_strjoin(mini->echo.args[i], "=");
    while (mini->envp_g[++k])
        if (ft_strncmp(mini->envp_g[k], arg, ft_strlen(arg)) == 0)
        {
            while (mini->envp_g[k][j] != '=')
                j++;
            j++;
            mini->dollar.value = ft_strjoin(mini->dollar.value, &mini->envp_g[k][j]);
        }
}

void ft_one_dollar(t_mini *mini, char *arg)
{
    mini->echo.args = malloc(sizeof(char *) * 2);
    mini->echo.args[0] = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
    mini->echo.args[0] = ft_strcpy(mini->echo.args[0], arg);
    mini->echo.args[1] = NULL;
}

void ft_print_num(t_mini *mini, int i)
{
    char *num;
    if (mini->echo.args[i][0] == '?')
    {
        num = ft_itoa(mini->exit_status);
        ft_putstr(num);
        ft_putstr(&mini->echo.args[i][1]);
    }
}

int ft_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return 1;
    return 0;
}
int ft_valid_dollar_arg(t_mini *mini, int i)
{
    int j = 0;
    while (mini->echo.args[i][j])
    {
        if (!ft_alphanum(mini->echo.args[i][j]))
            return 0;
        j++;
    }
    return 1;
}

void ft_dollar_syn(t_mini *mini, int i)
{
    int j = 0;
    mini->dollar.prefixx = 0;
    mini->dollar.suffixx = 0;
    while (mini->echo.args[i][j])
    {
        if (!ft_alphanum(mini->echo.args[i][j]))
        {
            if (mini->echo.args[i + 1])
            {
                mini->dollar.prefixx = 1;
                mini->dollar.prefix = (char *)malloc(sizeof(char) * (ft_strlen(&mini->echo.args[i][j]) + 2));
                if (j == 0)
                    mini->dollar.prefix = "$";
                mini->dollar.prefix = ft_strjoin(mini->dollar.prefix, &mini->echo.args[i][j]);
                while (mini->echo.args[i][j])
                {
                    mini->echo.args[i][j] = '\0';
                    j++;
                }
                break;
            }
            else
            {
                mini->dollar.suffixx = 1;
                mini->dollar.suffix = (char *)malloc(sizeof(char) * (ft_strlen(&mini->echo.args[i][j]) + 1));
                if (j == 0)
                    mini->dollar.suffix = "$";
                mini->dollar.suffix = ft_strjoin(mini->dollar.suffix, &mini->echo.args[i][j]);
                while (mini->echo.args[i][j])
                {
                    mini->echo.args[i][j] = '\0';
                    j++;
                }
            }
        }
        j++;
    }
}
void ft_get_value(t_mini *mini, char *arg)
{
    int i = 0;

    mini->dollar.value = "";
    if (mini->dollar_num > 1)
        mini->echo.args = ft_split(arg, '$');
    else if (mini->dollar_num == 1)
        ft_one_dollar(mini, arg);
    while (mini->echo.args[i])
    {
        if (mini->echo.args[i][0] != '?')
        {
            ft_dollar_syn(mini, i);
            if (mini->dollar.prefixx == 1 && !mini->args[i])
                mini->dollar.value = ft_strjoin(mini->dollar.value, mini->dollar.prefix);
            ft_env_dollar(mini, i);
            if (mini->dollar.prefixx == 1 && mini->args[i])
                mini->dollar.value = ft_strjoin(mini->dollar.value, mini->dollar.prefix);
            if (mini->dollar.suffixx == 1)
                mini->dollar.value = ft_strjoin(mini->dollar.value, mini->dollar.suffix);
        }
        else
            ft_print_num(mini, i);
        i++;
    }
}

void ft_get_num_dollar(t_mini *mini, char *arg)
{
    int i = 0;
    while (arg[i])
    {
        if (arg[i] == '$')
            mini->dollar_num++;
        i++;
    }
}

int ft_check_dollar(t_mini *mini)
{
    int i = 0;
    int j = 0;
    while (mini->args[i])
    {
        j = 0;
        while (mini->args[i][j])
        {
            if (mini->args[i][j] == '$')
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

void ft_dollar(t_mini *mini)
{
    int i = 0;
    int j = 1;
    int dollar = 0;

    if (ft_check_dollar(mini) == 1)
    {
       ft_skipe_quotes(mini);
        while (mini->args[i])
        {
            mini->dollar_num = 0;
            ft_get_num_dollar(mini, mini->args[i]);
            if (mini->args[i][0] == '$' && mini->args[i][1])
            {
                if ((mini->args[i][j] >= '0' && mini->args[i][j] <= '9'))
                {
                    // while ((mini->args[i][j] >= '0' && mini->args[i][j] <= '9'))
                    j++;
                    mini->args[i] = &mini->args[i][j];
                }
                else
                {
                    ft_get_value(mini, &mini->args[i][1]);
                    mini->args[i] = mini->dollar.value;
                }
            }
            i++;
        }
    }
}