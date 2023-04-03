/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:53:27 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/18 13:12:32 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	roff;
	size_t	loff;
	char	*ret;

	if (!set || !s1)
		return (NULL);
	loff = 0;
	while (s1[loff] && ft_strchr(set, s1[loff]))
		loff++;
	roff = ft_strlen(s1);
	while (roff && ft_strchr(set, s1[roff - 1]))
		roff--;
	ret = ft_substr(s1, loff, roff - loff);
	return (ret);
}
