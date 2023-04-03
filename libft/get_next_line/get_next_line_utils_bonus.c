/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:33:23 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/05/13 13:04:14 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_strlen(char *s)
{
	int	ret;

	ret = 0;
	while (s[ret])
		ret++;
	return (ret);
}

int	gnl_linelen(char *mem)
{
	int	ret;

	ret = 0;
	while (mem[ret] && mem[ret] != '\n')
		ret++;
	if (mem[ret] == '\n')
		ret++;
	return (ret);
}

void	gnl_strlcpy(char *dst, char *src, int size)
{
	if (!dst || !src)
		return ;
	while (size)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = 0;
}

char	*gnl_strchr(char *s, int c)
{
	unsigned char	temp;

	temp = c;
	while (*s || !temp)
	{
		if (*s == temp)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	s1len = gnl_strlen(s1);
	s2len = gnl_strlen(s2);
	ret = (char *) malloc((s1len + s2len + 1) * sizeof(char));
	if (!ret)
		return (0);
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = 0;
	free(s1 - s1len);
	return (ret - s1len - s2len);
}
