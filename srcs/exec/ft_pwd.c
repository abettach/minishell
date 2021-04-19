/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:08 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_count_pipes(t_mini *m)
{
	int j;
	int pipe;

	j = 0;
	pipe = 0;
	while (m->line[j])
	{
		if (m->line[j] == '|')
			pipe++;
		j++;
	}
	return (pipe);
}

void	ft_pwd(t_mini *m)
{
	g_v.exit_status = 0;
	getcwd(m->cwd, ft_strlen(m->cwd));
	ft_putstr_fd(m->cwd, 1);
	ft_putstr_fd("\n", 1);
}
