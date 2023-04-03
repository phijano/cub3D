/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:31:39 by phijano-          #+#    #+#             */
/*   Updated: 2023/03/23 10:32:23 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static void	getstep(t_cub *cub)
{
	if (cub->rc.raydirx < 0)
	{
		cub->rc.xstep = -1;
		cub->rc.sidex = (cub->player.x - cub->rc.mapx) * cub->rc.dx;
	}
	else
	{
		cub->rc.xstep = 1;
		cub->rc.sidex = (cub->rc.mapx + 1.f - cub->player.x) * cub->rc.dx;
	}
	if (cub->rc.raydiry < 0)
	{
		cub->rc.ystep = -1;
		cub->rc.sidey = (cub->player.y - cub->rc.mapy) * cub->rc.dy;
	}
	else
	{
		cub->rc.ystep = 1;
		cub->rc.sidey = (cub->rc.mapy + 1.f - cub->player.y) * cub->rc.dy;
	}
}

// If the player leaves the walls this would become an infinite loop and lead
// to segfaults.
static void	digitaldiferentialanalysis(t_cub *cub)
{
	while (!cub->rc.wallhit)
	{
		if (cub->rc.sidex < cub->rc.sidey)
		{
			cub->rc.sidex += cub->rc.dx;
			cub->rc.mapx += cub->rc.xstep;
			cub->rc.sidehit = 0;
		}
		else
		{
			cub->rc.sidey += cub->rc.dy;
			cub->rc.mapy += cub->rc.ystep;
			cub->rc.sidehit = 1;
		}
		if (cub->mdata.cmap[cub->rc.mapy][cub->rc.mapx] == '1')
			cub->rc.wallhit = 1;
	}
}

static void	gethitinfo(t_cub *cub, unsigned int x)
{
	if (!cub->rc.sidehit)
		cub->sight[x].dist = cub->rc.sidex - cub->rc.dx;
	else
		cub->sight[x].dist = cub->rc.sidey - cub->rc.dy;
	if (!cub->rc.sidehit)
	{
		if (cub->player.x > cub->rc.mapx)
			cub->sight[x].worient = 2;
		else
			cub->sight[x].worient = 0;
		cub->sight[x].wtexc = cub->sight[x].dist * cub->rc.raydiry;
		cub->sight[x].wtexc += cub->player.y;
	}
	else
	{
		if (cub->player.y > cub->rc.mapy)
			cub->sight[x].worient = 1;
		else
			cub->sight[x].worient = -1;
		cub->sight[x].wtexc = cub->sight[x].dist * cub->rc.raydirx;
		cub->sight[x].wtexc += cub->player.x;
	}
	cub->sight[x].wtexc -= floorf(cub->sight[x].wtexc);
}

// camx will be -1 for the first ray, 0 for the middle one and 1 for
// the last one. This means camx will move in the range [-1, 1] and so it can
// be used to scale the camvector to add it to the playerposvector in order to
// get the direction vector of the ray for a given x.
void	ft_raycasting(t_cub *cub)
{
	unsigned int	x;
	float			camx;

	x = 0;
	while (x < WINWIDTH)
	{
		camx = 2. * x / WINWIDTH - 1;
		cub->rc.raydirx = cub->player.dirx + cub->player.camvectx * camx;
		cub->rc.raydiry = cub->player.diry + cub->player.camvecty * camx;
		cub->rc.dx = fabsf(1 / cub->rc.raydirx);
		cub->rc.dy = fabsf(1 / cub->rc.raydiry);
		cub->rc.mapx = cub->player.x;
		cub->rc.mapy = cub->player.y;
		cub->rc.wallhit = 0;
		getstep(cub);
		digitaldiferentialanalysis(cub);
		gethitinfo(cub, x);
		x++;
	}
}
