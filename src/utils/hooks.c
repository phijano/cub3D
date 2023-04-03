/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:08:09 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/27 11:33:10 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

// Rotation matrixes! Yay!
// The rotated vectors can easily be calculated by doing:
// (cosA -sinA)(X)
// (sinA  cosA)(Y)
// Where A is the angle a vector (X, Y) rotates.
static void	rotate(t_player *p, float a)
{
	const float	olddirx = p->dirx;
	const float	oldcamx = p->camvectx;
	const float	cosval = cosf(a);
	const float	sinval = sinf(a);

	p->dirx = olddirx * cosval - p->diry * sinval;
	p->diry = olddirx * sinval + p->diry * cosval;
	p->camvectx = oldcamx * cosval - p->camvecty * sinval;
	p->camvecty = oldcamx * sinval + p->camvecty * cosval;
}

static void	move(t_cub *cub, float xdir, float ydir)
{
	float		newx;
	float		newy;
	const float	mvspeed = 0.1;

	newx = cub->player.x + xdir * mvspeed;
	newy = cub->player.y + ydir * mvspeed;
	if (cub->mdata.cmap[(int)cub->player.y]
		[(int)(newx + xdir * 0.00001)] != '1')
		cub->player.x = newx;
	if (cub->mdata.cmap[(int)(newy + ydir * 0.00001)]
		[(int)cub->player.x] != '1')
		cub->player.y = newy;
}

void	keyhooks(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(cub->mlx);
		return ;
	}
}

void	mouserotate(double x, double y, void *param)
{
	float	a;
	t_cub	*cub;

	cub = param;
	(void)y;
	if (x != cub->halfwidth)
	{
		a = atanf((x - cub->halfwidth) * 0.005);
		rotate(&cub->player, a);
		mlx_set_mouse_pos(cub->mlx, cub->halfwidth, cub->halfheight);
	}
}

// 0.0872... equals ~5º
void	mainhook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate(&cub->player, -0.08726646259971647884618453842443);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate(&cub->player, 0.08726646259971647884618453842443);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move(cub, cub->player.dirx, cub->player.diry);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move(cub, -cub->player.dirx, -cub->player.diry);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move(cub, -cub->player.camvectx, -cub->player.camvecty);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move(cub, cub->player.camvectx, cub->player.camvecty);
	lineupdate(param);
	updateminimap(cub);
}
