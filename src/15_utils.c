/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:18:28 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 08:31:19 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

unsigned char	*ft_strjoin_free_s1(unsigned char **s1, unsigned char *s2)
{
	int				i;
	int				j;
	unsigned char	*new_str;

	i = 0;
	j = 0;
	if (*s1 != NULL)
		i = ft_strlen((char *)*s1);
	new_str = malloc((i + ft_strlen((char *)s2) + 1) * sizeof(unsigned char));
	if (!new_str)
		return (NULL);
	i = 0;
	if (*s1 != NULL)
	{
		while ((*s1)[i])
		{
			new_str[i] = (*s1)[i];
			i++;
		}
	}
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free (*s1);
	return (new_str);
}

unsigned char	*ft_str_unsigned_join(unsigned char *s1, unsigned char *s2)
{
	int		i;
	int		j;
	unsigned char	*new_str;

	i = -1;
	j = -1;
	new_str = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1) * sizeof(unsigned char));
	if (!new_str)
		return (NULL);
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++j])
	{
		new_str[i] = s2[j];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = -1;
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++j])
	{
		new_str[i] = s2[j];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	i = 0;
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (((ptr_s1[i] || ptr_s2[i]) != '\0') && i < n)
	{
		if ((ptr_s1[i] - ptr_s2[i]) < 0)
		{
			return (ptr_s1[i] - ptr_s2[i]);
		}
		else if ((ptr_s1[i] - ptr_s2[i]) > 0)
		{
			return (ptr_s1[i] - ptr_s2[i]);
		}
		i++;
	}
	return (0);
}

static void	put_value(char *str, int index, int n)
{
	int	index2;

	index2 = index;
	if (n == 0)
		str[0] = 0 + 48;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = (n / 10);
			str[(index - 1)] = 8 + 48;
			index--;
		}
		str[0] = '-';
		n = n * -1;
	}
	str[index2] = '\0';
	index--;
	while (n != 0)
	{
		str[index] = (n % 10) + 48;
		n = n / 10;
		index--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;
	int		cp_n;

	index = 1;
	cp_n = n;
	while ((cp_n / 10) != 0)
	{
		cp_n = cp_n / 10;
		index++;
	}
	if (n < 0)
		index++;
	str = (char *)malloc((index + 1) * sizeof(char));
	if (!str)
		return (NULL);
	put_value(str, index, n);
	return (str);
}
