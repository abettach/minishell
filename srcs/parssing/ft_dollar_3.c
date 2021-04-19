/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:35:34 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_do_if_3(t_mini *m)
{
	char	*num;
	char	*tmp;
	int		j;

	j = 0;
	m->d.i += 2;
	tmp = ft_strdup(m->d.new_line);
	free(m->d.new_line);
	m->d.new_line = NULL;
	num = ft_itoa(g_v.exit_status);
	m->d.new_line = ft_strjoin(tmp, num);
	while (num[j])
	{
		m->d.new_line[m->d.j] = num[j];
		j++;
		m->d.j++;
	}
	free(num);
	free(tmp);
}
