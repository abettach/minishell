/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:35:52 by abettach          #+#    #+#             */
/*   Updated: 2021/03/01 17:36:08 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_multiline(t_mini *mini)
{
    int i = 0;
    int quotes_open = 0;
    int quotes_closed = 1;
    int inside_quotes = 0;
    while (mini->line[i])
    {
        if (mini->line[i] == 34 && mini->line[i-1] != 92)
        {
            if (quotes_open == 1)
            {
                quotes_closed = 1;
                quotes_open = 0;
                inside_quotes = 0;
            }
            else
            {
                quotes_open = 1;
                quotes_closed = 0;
                inside_quotes = 1;
            }
        }
        i++;
    }
    if (quotes_closed == 0)
        return 1;
    return 0;
}
int ft_syntax_error(t_mini *mini)
{
    int i = 0;
    if (ft_multiline(mini) == 1)
        return 100;
    else
        while (mini->line[i])
        {
            if ((mini->line[i] == '>' && mini->line[i + 1] == '>' &&
                 mini->line[i + 2] == '>' && mini->line[i + 3] != '>') ||
                (mini->line[i] == '>' && mini->line[i + 2] == '>'))
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
            if ((mini->line[i] == '<' || mini->line[i] == '>') && !mini->line[i + 1])
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
    else if (i == 100)
        ft_error("Minishell : multiline commands ERROR","\n","");
    else if (i == 0)
        return 0;
    return 1;
}