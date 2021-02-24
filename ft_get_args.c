/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:28 by abettach          #+#    #+#             */
/*   Updated: 2021/02/23 15:41:23 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_check_args(t_mini *mini)
{
	int i = 0;

	while (i < mini->ArgsNum && mini->args[i])
	{
		if ((mini->args[i][0] == '~' && mini->args[i][1] == '/') || (mini->args[i][0] == '~' && mini->args[i][1] == '\0'))
		{
			// if (ft_strcmp(mini->home, "ERROR") == 0)
			// {
			// 	ft_error("cd: HOME not set","","\n");
			// 	break;
			// }
			// else
				mini->args[i] = ft_strjoin(mini->home, &mini->args[i][1]);
		}
		i++;
	}
}

int ft_get_args(t_mini *mini)
{
	int i = -1;
	int arg = -1;
	int carg = 0;
	mini->args = ft_split(mini->line, ' ');
	while (mini->args[++i]);
	mini->ArgsNum = i;
	i = 0;
	return 0;
}
