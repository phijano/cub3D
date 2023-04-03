/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:01:42 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/16 13:23:20 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	val;

	temp = (unsigned char *) s;
	val = c;
	while (n--)
	{
		if (*temp == val)
			return (temp);
		temp++;
	}
	return (NULL);
}
