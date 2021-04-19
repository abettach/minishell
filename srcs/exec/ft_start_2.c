/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:40:19 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_start_minishell_2(t_mini *m)
{
	ft_check_home(m);
	ft_run_command(m);
	ft_dup2(m);
	if (m->check_pipe == 0)
		ft_free_no_pipe(m);
	if (m->home_error)
	{
		free(m->home_error);
		m->home_error = NULL;
	}
}
