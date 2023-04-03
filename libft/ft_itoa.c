/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:09:47 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/07/16 12:41:09 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_prepnum(int n, int *isneg, int *numlen)
{
	unsigned int	temp;

	*numlen = 0;
	if (!n)
		*numlen = 1;
	*isneg = 0;
	if (n < 0)
	{
		*isneg = 1;
		temp = -n;
	}
	else
		temp = n;
	return (temp);
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				numlen;
	int				isneg;
	unsigned int	temp;

	temp = ft_prepnum(n, &isneg, &numlen);
	while (n)
	{
		n /= 10;
		numlen++;
	}
	ret = ft_calloc(numlen + isneg + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (isneg)
		*ret = '-';
	isneg = !isneg;
	while (numlen)
	{
		ret[numlen-- - isneg] = temp % 10 + '0';
		temp /= 10;
	}
	return (ret);
}
