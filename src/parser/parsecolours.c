/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecolours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:51 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/27 11:50:00 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static int	getoffset(char *line, int i, t_cub *cub)
{
	if (line[i++] != ',')
		frerrxit("RGB elements must be separated by a comma.", cub);
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

static int	gethex(char *line, t_cub *cub)
{
	int	ret;
	int	i;

	if (!ft_isdigit(*line))
		frerrxit("Illegal colour declaration.", cub);
	ret = atouc(line, &i, cub) << 24;
	i = getoffset(line, i, cub);
	line += i;
	if (!ft_isdigit(*line))
		frerrxit("Illegal colour declaration.", cub);
	ret += atouc(line, &i, cub) << 16;
	i = getoffset(line, i, cub);
	line += i;
	if (!ft_isdigit(*line))
		frerrxit("Illegal colour declaration.", cub);
	ret += atouc(line, &i, cub) << 8;
	while (line[i])
		if (!ft_isspace(line[i++]))
			frerrxit("Trailing bad stuff in colour declaration.", cub);
	ret += 255;
	return (ret);
}

void	getcolours(int colstored[2], char *line, t_cub *cub)
{
	int	*colourdir;

	while (ft_isspace(*line))
		line++;
	if (!colstored[0] && !ft_strncmp(line, "F", 1))
	{
		colourdir = &cub->mdata.floorc;
		colstored[0] = 1;
	}
	else if (!colstored[1] && !ft_strncmp(line, "C", 1))
	{
		colourdir = &cub->mdata.ceilic;
		colstored[1] = 1;
	}
	else
		frerrxit("Bad/dup colour identifier. Accepted: [F, C]", cub);
	line++;
	while (ft_isspace(*line))
		line++;
	*colourdir = gethex(line, cub);
}
