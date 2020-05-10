/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:59:37 by kdeloise          #+#    #+#             */
/*   Updated: 2019/04/22 16:59:38 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static	char		**memfree(char **fr, int i)
{
	while (--i >= 0)
	{
		free(fr[i]);
		fr[i] = 0;
	}
	free(fr);
	fr = 0;
	return (fr);
}

static	int			ft_count_words(char const *s, int c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static	size_t		ft_wordsize(char const *s, int c)
{
	int count;

	count = 0;
	while (*s != c && *s != 0)
	{
		s++;
		count++;
	}
	return (count);
}

static	char		*ft_word(char const *s, int c)
{
	char	*strnew;
	int		i;
	size_t	size;

	i = 0;
	size = ft_wordsize(s, c);
	strnew = (char *)ft_memalloc(size + 1);
	if (!strnew)
		return (0);
	while (size != 0)
	{
		strnew[i++] = *s++;
		size--;
	}
	return (strnew);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**str;
	size_t		words;
	size_t		i;

	if (!s)
		return (0);
	i = 0;
	words = ft_count_words(s, c);
	str = (char **)ft_memalloc((words + 1) * sizeof(char *));
	if (!str)
		return (0);
	if (*s == 0)
		return (str);
	while (i < words)
	{
		while (*s == c)
			s++;
		str[i] = ft_word(s, c);
		if (!str[i++])
			return (memfree(str, i));
		s += ft_wordsize(s, c) + 1;
	}
	str[words] = 0;
	return (str);
}
