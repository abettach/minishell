/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:43:01 by abettach          #+#    #+#             */
/*   Updated: 2021/03/21 18:13:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_bzero(void *s, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		d[i] = 0;
		i++;
	}
	return ;
}

char		*clean_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char		*ft_chr(const char *s, int c)
{
	char		c2;
	char		*str;
	int			i;

	c2 = (char)c;
	str = (char *)s;
	i = 0;
	if (c2 == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == c2)
			return (str + i);
		i++;
	}
	return (NULL);
}

void		*ft_free2(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
