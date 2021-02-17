#include "minishell.h"

void ft_putchar(char c)
{
	write(1, &c, 1);
}
void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int char_test(char *command, char *str)
{
	int i = 0;

	if (command[i] == '\0' || command[i] == '\n')
	{
		// ft_putstr("NO COMMANDE :\n");
		return 0;
	}
	while (command[i])
	{
		if ((command[i] - str[i]) == 0)
			i++;
		else
			return 0;
	}
	return 1;
}

int ft_ischar(char c)
{
	if ((c >= 'a' && c <= 'z') || ((c >= 'A') && (c <= 'Z')) || (c == '-') || (c == '|') || (c == '"') || (c == '.') || (c == '/') || (c == '~') || (c == '&') || (c == '>') || (c >= '0' && c <= '9') || c == ';' || c == '=' || (c == '*') || (c == '$') || (c == 39) || (c == '<') || (c == 92) || (c == '\t') || (c == '#') || (c == '%') || (c == '{') || (c == '}') || (c == ':') || (c == '!') || (c == '@') || (c == '`') || (c == '.') || (c == ',') || (c == '^') || (c == '*') || (c == '(') || (c == ')') || (c == '+') || (c == '?') || (c == '_'))
		return 1;
	return 0;
}

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;
	unsigned char *s11;
	unsigned char *s22;

	i = 0;
	if (s1 == NULL)
		return 1;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while ((s11[i] || s22[i]))
	{
		if (s11[i] != '\0' && s22[i] == '\0')
			return (s11[i]);
		if (s11[i] == '\0' && s22[i] != '\0')
			return (-s22[i]);
		if (s11[i] > s22[i])
			return (s11[i] - s22[i]);
		if (s11[i] < s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

char **ft_strjoin2(char **s1, char *s2)
{
	char *ret;
	int i;
	int j = 0;
	int count = 0;
	i = (ft_strlen(s2) + 1);
	while (s1[i])
		i++;
	s1[i] = (char *)malloc(sizeof(char) * (ft_strlen(s2) + 1));
	while (s2[j])
	{
		s1[i][j] = s2[j];
		j++;
	}
	s1[i][j] = '\0';
	i++;
	s1[i] = NULL;
	return (s1);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	unsigned char *s11;
	unsigned char *s22;

	i = 0;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while ((s11[i] || s22[i]) && i < n)
	{
		if (s11[i] != '\0' && s22[i] == '\0')
			return (s11[i]);
		if (s11[i] == '\0' && s22[i] != '\0')
			return (-s22[i]);
		if (s11[i] > s22[i])
			return (s11[i] - s22[i]);
		if (s11[i] < s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

char *ft_strcpy(char *dst, const char *src)
{
	size_t i;

	i = 0;
	src = (char *)src;
	if (!(src))
		return (0);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int ft_equal_check(t_mini *mini, char *arg)
{
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return 1;
		i++;
	}
	return 0;
}

char *ft_strlcpy(char *dst, const char *src, int size)
{
	int i;

	i = 0;
	src = (char *)src;

	while (src[i] != '\0' && size != 0 && (i < (size + 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void ft_error(char *error_msg, char *command, char *line)
{
	ft_putstr(error_msg);
	ft_putstr(command);
	ft_putstr(line);
}

int		ft_atoi(const char *str)
{
	int s;
	int r;

	s = 1;
	r = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n'
			|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	r = r * s;
	return (r);
}



static int		num_len(int n)
{
	int	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				numlen;
	unsigned int	nb;

	numlen = num_len(n);
	nb = n;
	if (n < 0)
	{
		nb = -n;
		numlen++;
	}
	if (!(str = malloc(numlen + 1)))
		return (0);
	str[numlen] = '\0';
	str[--numlen] = nb % 10 + '0';
	while (nb /= 10)
		str[--numlen] = nb % 10 + '0';
	if (n < 0)
		*(str) = '-';
	return (str);
}