/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atouc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senari <ntamayo-@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:55:33 by senari            #+#    #+#             */
/*   Updated: 2023/03/27 11:50:49 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	atouc(const char *s, int *offset, t_cub *cub)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		ret *= 10;
		ret += s[i] - '0';
		if (ret > 255)
			frerrxit("Colour overflow. Accepted: [0, 255]", cub);
		i++;
	}
	if (offset)
		*offset = i;
	return (ret);
}
