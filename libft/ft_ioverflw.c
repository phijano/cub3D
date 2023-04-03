/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioverflw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:37:36 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/12/25 20:48:49 by senari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(const char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int	ft_ioverflw(char *str, int num)
{
	int	len;

	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	len = numlen(str);
	if (*str == '-')
		return (!num || len > 11 || (len == 11 && str[1] > '2'));
	return (num == -1 || len > 10 || (len == 10 && str[0] > '2'));
}
