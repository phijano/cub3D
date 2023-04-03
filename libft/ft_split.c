/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:35:40 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/18 12:23:14 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stringalloc(char const **str, char c)
{
	char	*ret;
	size_t	wlen;

	wlen = 0;
	while (str[0][wlen] && str[0][wlen] != c)
		wlen++;
	ret = malloc(sizeof(char) * (wlen + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, *str, wlen + 1);
	*str += wlen;
	return (ret);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if ((*s != c && *(s + 1) == c) || (*s != c && !*(s + 1)))
			words++;
		s++;
	}
	return (words);
}

static void	ft_destroyer(char **arr, size_t words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
}

static int	ft_strstringer(char **ret, size_t words, char c, char const *s)
{
	size_t	retindex;

	retindex = 0;
	while (retindex < words)
	{
		while (*s == c)
			s++;
		ret[retindex] = ft_stringalloc(&s, c);
		if (!ret[retindex])
		{
			ft_destroyer(ret, retindex);
			return (1);
		}
		retindex++;
	}
	ret[retindex] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	ret = malloc(sizeof(char *) * (words + 1));
	if (!ret)
		return (NULL);
	if (ft_strstringer(ret, words, c, s))
		return (NULL);
	return (ret);
}
