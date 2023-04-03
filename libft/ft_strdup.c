/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:18:30 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/18 12:45:14 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*start;
	size_t	len;

	len = ft_strlen(s1);
	start = malloc(sizeof(char) * (len + 1));
	if (!start)
		return (NULL);
	ft_strlcpy(start, s1, len + 1);
	return (start);
}
