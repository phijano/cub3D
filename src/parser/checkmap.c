/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:25:33 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/23 15:22:17 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	isvalid(char c)
{
	return (c == '1' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

static void	charcheck(char *line, unsigned int i, unsigned int lo, t_cub *cub)
{
	if (!line[i])
		return ;
	if (!isvalid(line[i]))
		frerrxit("Illegal tile found in the map.", cub);
	if (line[i] != '1')
	{
		if ((!line[i + 1] || line[i + 1] == ' ')
			|| (!lo || lo == cub->mdata.ysize - 1)
			|| (lo > 0 && !isvalid(cub->mdata.cmap[lo - 1][i]))
			|| (lo < cub->mdata.ysize - 1
				&& !isvalid(cub->mdata.cmap[lo + 1][i])))
			frerrxit("Map isn't closed.", cub);
	}
}

// For this shit to work N/S have to be inverted so that N(0,-1) and S(0,1). 
// W T F
// Try to find out why the hell controls and the screen flip when N/S have their
// true value.
// So apparently is because of the way the map is stored in memory. Since
// characters of a row (and thus the X axis) progress positively to the right,
// but the rows themselves progress positively downwards:
//             [1, N, 1]
// arr[3][3] = [1, 0, 1]   The character in arr[0][1] is N while the one in
//             [1, S, 1]   arr[2][1] is S.
// Which means N/S are flipped in map coords and so the math must be adjusted to
// it.
static void	playerinfo(char c, unsigned int i, unsigned int j, t_cub *cub)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		if (cub->player.x != 0)
			frerrxit("Dopplegangers?!?!", cub);
		cub->player.x = i + 0.5;
		cub->player.y = j + 0.5;
		cub->player.dirx = 0;
		cub->player.diry = 0;
		if (c == 'N')
			cub->player.diry = -1;
		else if (c == 'W')
			cub->player.dirx = -1;
		else if (c == 'S')
			cub->player.diry = 1;
		else
			cub->player.dirx = 1;
		cub->player.camvectx = -cub->player.diry * fabsf(tanf(FOV / 2));
		cub->player.camvecty = cub->player.dirx * fabsf(tanf(FOV / 2));
	}
}

// For each character of the line:
// Skip spaces until a 1 is found. If anything else is found after spaces,
// throw an error.
// Then, inside charcheck:
// Check if the character is valid.
// If it is BUT it isn't a 1, check wether it is the last char in the line
// or there is a space after it. Also check if we are looking at the first or
// last line, since those can only have spaces or 1s. Finally, if we aren't
// on the first or last line, check if the character over or under isn't valid.

static void	checkline(char *line, unsigned int lineno, t_cub *cub)
{
	unsigned int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (!line[i])
				continue ;
			else if (line[i] != '1')
				frerrxit("Illegal tile found after space.", cub);
		}
		charcheck(line, i, lineno, cub);
		playerinfo(line[i], i, lineno, cub);
		i++;
	}
}

void	checkmap(char **map, t_cub *cub)
{
	unsigned int	i;

	i = 0;
	while (map[i])
	{
		checkline(map[i], i, cub);
		i++;
	}
	if (cub->player.x == 0)
		frerrxit("No players found.", cub);
}
