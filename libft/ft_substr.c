/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:35:34 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/18 13:15:23 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start)
	{
		ret = malloc(sizeof(char));
		if (!ret)
			return (NULL);
		*ret = 0;
		return (ret);
	}
	if (slen - start < len)
		len = slen - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s[start], len + 1);
	return (ret);
}
