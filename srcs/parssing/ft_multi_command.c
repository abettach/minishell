/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:17:51 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			is_space_multicommand(t_mini *m)
{
	int		i;

	i = 0;
	while (m->line[i])
	{
		if (m->line[i] == ';')
			if (m->line[i - 1] == ' ' || m->line[i + 1] == ' ')
				return (1);
		i++;
	}
	return (0);
}

void		ft_multi_command(t_mini *m)
{
	char	*new_multi_command;
	int		i;

	i = 0;
	m->m_cmd = ft_split(m->line, ';');
	while (m->m_cmd[i])
	{
		new_multi_command = ft_strdup(m->m_cmd[i]);
		free(m->m_cmd[i]);
		m->m_cmd[i] = ft_strtrim(new_multi_command, ' ');
		free(new_multi_command);
		i++;
	}
}

void		ft_check_multi_command(t_mini *m)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	while (m->line[i])
	{
		if (m->line[i] == ';')
		{
			index = 1;
			ft_multi_command(m);
			break ;
		}
		i++;
	}
	if (index == 0)
	{
		m->m_cmd = malloc(sizeof(char *) * 1);
		m->m_cmd[0] = ft_strdup(m->line);
		m->m_cmd[1] = NULL;
	}
}
