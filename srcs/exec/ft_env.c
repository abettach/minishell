/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:10 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_mini *m)
{
	int i;

	i = 0;
	if (m->args[1])
	{
		ft_error("env: ", m->args[1], ": No such file or directory\n");
		g_v.exit_status = 127;
	}
	else
		g_v.exit_status = 0;
	if (m->args_num <= 1)
	{
		while (m->envp_g[i])
		{
			if (ft_strcmp(m->envp_g[i], "UNSETTHISVSRISBLE") != 0
			&& ft_equal_check(m->envp_g[i]) == 1)
			{
				ft_putstr_fd(m->envp_g[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
	}
}
