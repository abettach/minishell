/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_syn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:53:55 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			is_redirection(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' ||
		(line[i] == '>' && line[i + 1] == '>'))
			return (1);
		i++;
	}
	return (0);
}

void		ft_redirection_space_1(t_mini *m)
{
	if (m->line[m->v.i] == '>' && m->line[m->v.i + 1] != '>'
	&& m->line[m->v.i - 1] != '>')
	{
		if (m->line[m->v.i - 1] != ' ')
		{
			m->v.new_line[m->v.j] = ' ';
			m->v.j++;
		}
		if (m->line[m->v.i + 1] != ' ')
		{
			m->v.new_line[m->v.j] = m->line[m->v.i];
			m->v.j++;
			m->v.new_line[m->v.j] = ' ';
			m->v.i++;
			m->v.j++;
		}
	}
}

void		ft_redirection_space_2(t_mini *m)
{
	if (m->line[m->v.i] == '<')
	{
		if (m->line[m->v.i - 1] != ' ')
		{
			m->v.new_line[m->v.j] = ' ';
			m->v.j++;
		}
		if (m->line[m->v.i + 1] != ' ')
		{
			m->v.new_line[m->v.j] = m->line[m->v.i];
			m->v.j++;
			m->v.new_line[m->v.j] = ' ';
			m->v.i++;
			m->v.j++;
		}
	}
}

void		ft_redirection_space_3(t_mini *m)
{
	if (m->line[m->v.i] == '>' && m->line[m->v.i + 1] == '>')
	{
		if (m->line[m->v.i - 1] != ' ')
		{
			m->v.new_line[m->v.j] = ' ';
			m->v.j++;
		}
	}
	else if (m->line[m->v.i - 1] == '>'
	&& m->line[m->v.i - 2] == '>')
	{
		if (m->line[m->v.i] != ' ')
		{
			m->v.new_line[m->v.j] = ' ';
			m->v.j++;
		}
	}
}

void		ft_redirection_space(t_mini *m)
{
	int		space_nb;
	char	*tmp;

	m->v.i = 0;
	m->v.j = 0;
	space_nb = ft_space_nb(m, -1, 0);
	if (is_redirection(m->line) == 1)
	{
		m->v.new_line = (char *)malloc(sizeof(char) *
		(ft_strlen(m->line) + space_nb + 1));
		while (m->line[m->v.i])
		{
			ft_redirection_space_1(m);
			ft_redirection_space_2(m);
			ft_redirection_space_3(m);
			m->v.new_line[m->v.j] = m->line[m->v.i];
			m->v.i++;
			m->v.j++;
		}
		m->v.new_line[m->v.j] = '\0';
		free(m->line);
		tmp = m->v.new_line;
		m->line = ft_strdup(m->v.new_line);
		free(tmp);
	}
}
