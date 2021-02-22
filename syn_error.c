/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:35:52 by abettach          #+#    #+#             */
/*   Updated: 2021/02/22 15:50:50 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_syntax_error(t_mini *mini)
{
    int i = 0;
    while (mini->line[i])
    {
        if (mini->line[i] == '>' && mini->line[i + 1] == '>' &&
            mini->line[i + 2] == '>' && mini->line[i + 3] != '>')
            return 1;
        if (mini->line[i] == '>' && mini->line[i + 1] == ' ' &&
            mini->line[i + 2] == '<')
            return 2;
        if (mini->line[i] == '>' && mini->line[i + 1] == '>' &&
            mini->line[i + 2] == '>' && mini->line[i + 3] == '>')
            return 3;
        if (mini->line[i] == ';' && mini->line[i + 1] == ';')
            return 4;
        if (mini->line[0] == '|')
            return 5;
        if (mini->line[i] == '|' && mini->line[i + 1] == ' ' &&
            mini->line[i + 2] == '|')
            return 6;
        if ((mini->line[i] == '<' || mini->line[i] == '>' )&& !mini->line[i + 1])
            return 7;
        if (mini->line[i] == ';' && mini->line[i + 1] == '|')
            return 8;
        if (mini->line[i] == '|' && mini->line[i + 1] == ';')
            return 9;
        if (mini->line[0] == ';')
            return 10;
        i++;
    }
    return 0;
}

int syn_error(t_mini *mini)
{
    int i;

    i = ft_syntax_error(mini);
    if (i == 1)
        ft_error("syntax error near unexpected token ", "`>'", "\n");
    else if (i == 2)
        ft_error("syntax error near unexpected token ", "`<'", "\n");
    else if (i == 3)
        ft_error("syntax error near unexpected token ", "`>>'", "\n");
    else if (i == 4)
        ft_error("syntax error near unexpected token ", "`;;'", "\n");
    else if (i == 5 || i == 6)
        ft_error("syntax error near unexpected token ", "`|'", "\n");
    else if (i == 7)
        ft_error("syntax error near unexpected token ", "`newline'", "\n");
    else if (i == 8 || i == 10)
        ft_error("syntax error near unexpected token ", "`;'", "\n");
    else if (i == 9)
        ft_error("syntax error near unexpected token ", "`|'", "\n");
    else if (i == 0)
        return 0;
    return 1;
}