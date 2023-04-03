/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senari <ntamayo-@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:58:53 by senari            #+#    #+#             */
/*   Updated: 2023/03/27 11:51:00 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <math.h>

///////DEFINES//////////////////////////////////////////////////////////////////
# define WINWIDTH 800
# define WINHEIGHT 600

/**
 * Vision Field
 * Total angle of player vision, typically between 60 and 90 grades in games
 * its better to work with radians, 360 grades is 2π radianes
 * so 60 is π/3 radians, M_PI is a constant defined in math.h for π
 * if we want 90 grades it would be π/2, there is a constant defined in math.h
 * for that: M_PI_2
*/
# define FOV 1.1519173063162575207696359072024843908722954464375388010241463505

///////STRUCTURES///////////////////////////////////////////////////////////////
typedef struct s_mapdata
{
	char			**cmap;
	unsigned int	xsize;
	unsigned int	ysize;
	char			*npath;
	char			*wpath;
	char			*spath;
	char			*epath;
	int				floorc;
	int				ceilic;
}					t_mapdata;

typedef struct s_player
{
	float	x;
	float	y;
	float	dirx;
	float	diry;
	float	camvectx;
	float	camvecty;
}			t_player;

// In worient: -1(S), 0(E), 1(N), 2(W)
typedef struct s_vision_point
{
	float	dist;
	float	wtexc;
	int		worient;
}			t_vision_point;

typedef struct s_raycast
{
	int		wallhit;
	int		mapx;
	int		mapy;
	int		xstep;
	int		ystep;
	int		sidehit;
	float	sidex;
	float	sidey;
	float	dx;
	float	dy;
	float	raydirx;
	float	raydiry;
}			t_raycast;

typedef struct s_cub
{
	unsigned int	halfwidth;
	unsigned int	halfheight;
	t_mapdata		mdata;
	t_player		player;
	mlx_t			*mlx;
	mlx_texture_t	*ntex;
	mlx_texture_t	*wtex;
	mlx_texture_t	*stex;
	mlx_texture_t	*etex;
	mlx_image_t		*back;
	mlx_image_t		*mmap;
	mlx_image_t		*lines;
	t_raycast		rc;
	t_vision_point	sight[WINWIDTH];
}					t_cub;

///////GAME/////////////////////////////////////////////////////////////////////
void	ft_raycasting(t_cub *cub);

///////PARSING//////////////////////////////////////////////////////////////////
/**
* @brief Returns 0 for valid filenames or -1 for invalid ones.
*
* @param s: The name of the file.
* @param len: The length of the filename string.
*
* @return
*/
int		filecheck(const char *s, size_t len);

/**
* @brief A function that takes a string beginning by a digit character and
* returns the number it represent in the range [0, 255] or -1 if the value falls
* out of range. The character length of the number in the given string is passed
* onto the integer pointed to by the offset parameter ONLY if the given number
* falls in the range.
*
	* @param s: The string beginning by the first digit of the number to convert
	* to int.
	* @param offset: Pointer to an integer to store the length of the number,
	* or NULL.
	*
	* @return
*/
int		atouc(const char *s, int *offset, t_cub *cub);

/**
* @brief Opens and parses mapfile, storing the processed values in cub and
* exiting after printing the corresponding error if something goes wrong.
*
* @param mapfile: The path to the file containing the map information.
* @param cub: A pointer to the data structure where everything will be stored.
*/
void	parsemap(char *mapfile, t_cub *cub);

/**
* @brief Stores the path to the walls' textures inside cub. Error exits if
* something goes wrong.
*
* @param fd: File descriptor of the map file.
* @param cub: Pointer to the data structure.
*/
int		gettextures(char *line, t_cub *cub);

/**
* @brief Stores the floor's and ceiling's colours inside cub. Exits on error.
*
* @param fd: File descriptor of the map file.
* @param cub: Pointer to the data structure.
*/
void	getcolours(int colstored[2], char *line, t_cub *cub);

/**
* @brief Add spaces to the end of the lines shorter than the longest one in
* order to make the map a matrix and avoid segmenting when checking adjacent
* characters in checkmap.
*
* @param cub
*/
void	makeitsquared(t_cub *cub);

/**
* @brief Perform validity checks on the map. Frerrxit on error.
*
* @param cub
*/
void	checkmap(char **map, t_cub *cub);

///////GRAPHIC STUFF////////////////////////////////////////////////////////////
/**
* @brief Creates and puts the background to window.
*
* @param cub
*/
void	backpaint(t_cub *cub);

/**
* @brief Call raycast and update each of the lines printed to the window.
*
* @param cub
*/
void	lineupdate(t_cub *cub);

/**
* @brief Create the minimap image.
*
*
* @param cub
*/
void	loadminimap(t_cub *cub);

/**
* @brief Update the minimap image.
*
* @param cub
*/
void	updateminimap(t_cub *cub);

///////UTILS////////////////////////////////////////////////////////////////////
/**
* @brief Print "Error\n" followed by msg to stderr.
*
	* @param msg
	*/
void	errmsg(char *msg);

/**
* @brief Call errmsg and exit(1).
*
	* @param msg
	*/
void	errexit(char *msg);

/**
* @brief Frees all of cub's resources.
*
* @param cub
*/
void	freecub(t_cub *cub);

/**
* @brief Frees resources and call errexit.
*
	* @param msg
	* @param cub
	*/
void	frerrxit(char *msg, t_cub *cub);

/**
* @brief Checks if given character is a valid map character.
*
* @param c
*
* @return 
*/
int		isvalid(char c);

/**
* @brief Handles all key inputs.
*
	* @param keydata
	* @param param Pointer to whatever the function may need. In this case: cub.
	*/
void	keyhooks(mlx_key_data_t keydata, void *param);

/**
* @brief Handles mouse movement.
*
* @param x
* @param y
* @param param Pointer to the player struct.
*/
void	mouserotate(double x, double y, void *param);

/**
* @brief Handles screen updating.
*
	* @param param
	*/
void	mainhook(void *param);

#endif
