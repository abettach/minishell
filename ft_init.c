/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:39 by abettach          #+#    #+#             */
/*   Updated: 2021/03/04 16:29:27 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_mini *mini)
{
	char *arg;
	int j = -1;
	mini->shell_lvl--;
	arg = (char *)malloc(sizeof(char) * (ft_strlen(mini->args[1])));
	arg = "";
	if (mini->args[1])
		arg = ft_strjoin(arg,mini->args[1]);
	else
		arg = ft_strjoin(arg,"0");
	if (mini->shell_lvl >= mini->first_lvl)
	{
		arg = "SHLVL=";
		while (mini->envp_g[++j])
			if (ft_strncmp(mini->envp_g[j], arg, ft_strlen(arg)) == 0)
				mini->envp_g = ft_remove_unset(mini, j);
		arg = ft_strjoin(arg, ft_itoa(mini->shell_lvl));
		ft_strjoin2(mini->envp_g, arg);
	}
	else if (mini->shell_lvl < mini->first_lvl)
	{
		if ((arg[0] < '1' || arg[0] > '9') && (mini->args[2]))
			mini->exit_status = 255;
		waitpid(-1,0,0);
		exit(ft_atoi(arg));
	}
}

void ft_init(t_mini *mini)
{
	int i = 0;
	int j = -1;
	i = -1;
	mini->run_path = NULL;
	// mini->exit_status = 0;
	g_input_file = NULL;
}