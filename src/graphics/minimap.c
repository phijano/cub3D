/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:57:13 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/23 15:20:07 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	loadminimap(t_cub *cub)
{
	cub->mmap = mlx_new_image(cub->mlx, 120, 120);
	if (!cub->mmap)
		freecub(cub);
	mlx_image_to_window(cub->mlx, cub->mmap, WINWIDTH - 120, 0);
}

static unsigned int	getmapcolour(t_cub *cub, unsigned int i, unsigned int j)
{
	unsigned int	hex;
	int				mapx;
	int				mapy;

	hex = 0x050020CC;
	mapx = cub->player.x + i / 8.5 - 7;
	mapy = cub->player.y + j / 8.5 - 7;
	if (mapx >= 0 && mapx < (int)cub->mdata.xsize - 1
		&& mapy >= 0 && mapy < (int)cub->mdata.ysize - 1)
		if (cub->mdata.cmap[mapy][mapx] != '1'
			&& cub->mdata.cmap[mapy][mapx] != ' ')
			hex = 0x100070CC;
	return (hex);
}

void	updateminimap(t_cub *cub)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (j < 120)
	{
		i = 0;
		while (i < 120)
		{
			mlx_put_pixel(cub->mmap, i, j, getmapcolour(cub, i, j));
			i++;
		}
		j++;
	}
	mlx_put_pixel(cub->mmap, 59, 59, 0x726432CC);
	mlx_put_pixel(cub->mmap, 60, 59, 0x726432CC);
	mlx_put_pixel(cub->mmap, 59, 60, 0x726432CC);
	mlx_put_pixel(cub->mmap, 60, 60, 0x726432CC);
}
