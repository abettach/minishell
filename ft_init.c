/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:39 by abettach          #+#    #+#             */
/*   Updated: 2021/02/16 16:23:51 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_mini *mini)
{
	char *arg;
	int j = -1;
	mini->shell_lvl -= 1;
	if (mini->shell_lvl >= mini->first_lvl)
	{
		arg = "SHLVL=";
		while (mini->envp_g[++j])
			if (ft_strncmp(mini->envp_g[j], arg, ft_strlen(arg)) == 0)
				mini->envp_g = ft_remove_unset(mini, j);
		arg = ft_strjoin3(arg, mini->shell_lvl);
		ft_strjoin2(mini->envp_g, arg);
	}
	else if (mini->shell_lvl < mini->first_lvl)
	{
		waitpid(-1,0,0);
		exit(mini->exit_status);
	}
}

void ft_init(t_mini *mini)
{
	int i = 0;
	int j = -1;
	i = -1;
	mini->run_path = NULL;
	g_input_redirection = 0;
	g_output_redirection = 0;
	mini->STD = 1;
	g_double_input_redirection = 0;
	g_pipe = 0;
	g_input_file = NULL;
	g_output_file = NULL;
	g_double_input_redirection = 0;
	g_double_redirection = NULL;
}