/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_syn_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:05:31 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_space_nb(t_mini *m, int i, int space_nb)
{
	while (m->line[++i])
	{
		if (m->line[i] == '>' && m->line[i + 1] != '>')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 1] != ' ')
				space_nb++;
		}
		else if (m->line[i] == '<')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 1] != ' ')
				space_nb++;
		}
		else if (m->line[i] == '>' && m->line[i + 1] == '>')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 2] != ' ')
				space_nb++;
		}
	}
	return (space_nb);
}
