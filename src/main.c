/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:07:06 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/27 11:31:34 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	handleinputandinit(int argc, char **argv, t_cub *cub)
{
	if (argc == 1)
		errexit("Missing map. Usage: [./cube3D <<mapname>>.cub]");
	else if (argc > 2)
		errexit("Too many input arguments. Usage: [./cube3D <<mapname>>.cub]");
	if (filecheck(argv[1], ft_strlen(argv[1])) == -1)
		errexit("Invalid map format. Usage: [./cube3D <<mapname>>.cub]");
	cub->mdata.cmap = NULL;
	cub->mdata.npath = NULL;
	cub->mdata.wpath = NULL;
	cub->mdata.spath = NULL;
	cub->mdata.epath = NULL;
	cub->player.x = 0;
	cub->mlx = NULL;
	cub->ntex = NULL;
	cub->wtex = NULL;
	cub->stex = NULL;
	cub->etex = NULL;
}

static void	loadimgsandinit(t_cub *cub)
{
	cub->mlx = mlx_init(WINWIDTH, WINHEIGHT, "N&P's Cube3D!", false);
	if (!cub->mlx)
		frerrxit("MLX init failed!", cub);
	cub->ntex = mlx_load_png(cub->mdata.npath);
	cub->wtex = mlx_load_png(cub->mdata.wpath);
	cub->stex = mlx_load_png(cub->mdata.spath);
	cub->etex = mlx_load_png(cub->mdata.epath);
	if (!cub->ntex || !cub->wtex || !cub->stex || !cub->etex)
		frerrxit("Failed to load png textures.", cub);
	cub->halfwidth = WINWIDTH / 2;
	cub->halfheight = WINHEIGHT / 2;
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, cub->halfwidth, cub->halfheight);
	cub->lines = mlx_new_image(cub->mlx, WINWIDTH, WINHEIGHT);
	if (!cub->lines)
		frerrxit("Lines allocation failed!", cub);
}

/*void	leakcheck(void)
{
	system("leaks cube3D");
}

void	infodump(t_cub *cub)
{
	unsigned int	i;

	i = 0;
	printf("Dir(%f, %f). Cam(%f, %f)\n", cub->player.dirx, cub->player.diry,
		cub->player.camvectx, cub->player.camvecty);
	printf("Textures:\n\tNO: %s\n\tWE: %s\n\tSO: %s\n\tEA: %s\nColors:\n\tF: \
%x\n\tC: %x\nMap:\n", cub->mdata.npath, cub->mdata.wpath, cub->mdata.spath,
		cub->mdata.epath, cub->mdata.floorc, cub->mdata.ceilic);
	while (i < cub->mdata.ysize)
		printf("%s\n", cub->mdata.cmap[i++]);
	printf("Player:\n\tX: %f\n\tY: %f\n", cub->player.x, cub->player.y);
}*/

// Right before handleinputandinit:
	/** atexit(leakcheck); */

// Right after parsemap:
	/** infodump(&cub); */

int	main(int argc, char **argv)
{
	t_cub	cub;

	handleinputandinit(argc, argv, &cub);
	parsemap(argv[1], &cub);
	loadimgsandinit(&cub);
	backpaint(&cub);
	loadminimap(&cub);
	mlx_key_hook(cub.mlx, keyhooks, &cub);
	mlx_cursor_hook(cub.mlx, mouserotate, &cub);
	mlx_loop_hook(cub.mlx, mainhook, &cub);
	mlx_loop(cub.mlx);
	freecub(&cub);
	return (0);
}
