/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:18:22 by abettach          #+#    #+#             */
/*   Updated: 2021/02/25 16:49:35 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  int     retur(char c1, const char *c2)
{
    int         i;
    i = 0;
    while (c2[i])
    {
        if (c1 == c2[i])
            return (1);
        i++;
    }
    return (0);
}
char            *ft_strtrim(char const *s1, char const *set)
{
    char        *con;
    size_t      len;
    size_t      i;
    i = 0;
	con = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	con =  "";
    con = ft_strjoin(con,s1);
    if (con == 0)
        return (0);
    while (retur(con[i], set) == 1)
        i++;
    len = ft_strlen(con) - 1;
    while (len > 0)
    {
        if (retur(con[len], set) == 0)
            break ;
        con[len] = '\0';
        len--;
    }
    return (ft_strdup(con + i));
}

int 	finde_next(char *ptr, int i, char c)
{
	
	while (ptr[i])
	{
		if (ptr[i] == c)
		{
			return(i);
		}
		i++;
	}
	return(i);
}

static	int			c_word(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = finde_next(str, i,str[i]);
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i] != c && str[i + 1] == '\0')
			count++;
	}
	return (count);
}

static	void		ft_free(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(str);
}

static	char		*remplir(char *s, int *k, char c)
{
	int		i;
	int		start;
	int		end;
	char	*str;
	int startt;
	i = *k;
	while (s[i] == c)
		i++;
	start = i;
	startt = i;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i = finde_next(s, i,s[i]);
		}
		i++;
	
	}
	end = i;
	*k = i;
	while(startt < end)
		startt++;
	str = ft_substr(s, start, (end - start ));
	if (str == NULL)
		return (NULL);
	return (str);
}

char				**ft_split(char const *s, char c)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = -1;
	str = ft_strtrim(s, &c);

	j = c_word(str, c);
	tab = (char **)malloc((j + 1) * sizeof(char*));
	k = 0;
	while (++i < j)
		if ((tab[i] = remplir(str, &k, c)) == NULL)
		{
			ft_free(tab, str);
			return (0);
		}
	tab[i] = NULL;
	return (tab);
}

