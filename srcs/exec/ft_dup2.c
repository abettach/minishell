/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:16:55 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_free_args_to_sort(t_mini *m)
{
	int i;

	i = 0;
	while (m->args_to_sort[i])
	{
		free(m->args_to_sort[i]);
		m->args_to_sort[i] = NULL;
		i++;
	}
	if (m->args_to_sort)
		free(m->args_to_sort);
}

void		ft_dup2(t_mini *m)
{
	int fdd;

	if (m->std == 1)
		fdd = dup(0);
	else
		fdd = dup(1);
	dup2(fdd, m->std);
	close(fdd);
}
