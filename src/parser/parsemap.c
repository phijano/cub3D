/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:40:33 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/21 21:56:50 by senari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"
#include <fcntl.h>

static int	openmap(char *mapfile)
{
	int	fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		errexit("Unable to open provided map file.");
	return (fd);
}

static void	getconfig(int fd, t_cub *cub)
{
	char	*temp;
	int		colstored[2];

	colstored[0] = 0;
	colstored[1] = 0;
	while (!colstored[0] || !colstored[1]
		|| !cub->mdata.npath || !cub->mdata.spath
		|| !cub->mdata.epath || !cub->mdata.wpath)
	{
		temp = get_next_line(fd);
		if (!temp)
			frerrxit("Map reading failed! Or not all fields are present.", cub);
		if (gettextures(temp, cub))
			getcolours(colstored, temp, cub);
		free(temp);
	}
}

	//printf("NO: [%s]\nWE: [%s]\nSO: [%s]\nEA: [%s]\nF: [%x]\nC: [%x]\n", 
//cub->mdata.npath, cub->mdata.wpath, cub->mdata.spath, cub->mdata.epath, 
//cub->mdata.floorc, cub->mdata.ceilic);

static char	*getfirstmapline(int fd)
{
	char	*ret;
	int		i;

	ret = get_next_line(fd);
	while (ret)
	{
		i = 0;
		while (ret[i] == ' ')
			i++;
		if (ret[i] == '1')
			return (ret);
		else if (ret[i] && ret[i] != '\n')
			return (NULL);
		free(ret);
		ret = get_next_line(fd);
	}
	return (ret);
}

static void	getmapline(int fd, t_cub *cub)
{
	char	*in;
	char	*temp;
	char	*onelinemap;

	onelinemap = getfirstmapline(fd);
	if (!onelinemap)
		frerrxit("Map contains invalid char.", cub);
	in = get_next_line(fd);
	while (in)
	{
		temp = onelinemap;
		onelinemap = ft_strjoin(onelinemap, in);
		if (!onelinemap)
			frerrxit("Failed to join onelinemap D:", cub);
		free(temp);
		free(in);
		in = get_next_line(fd);
	}
	cub->mdata.cmap = ft_split(onelinemap, '\n');
	if (!cub->mdata.cmap)
		frerrxit("Failed to split the map in rows.", cub);
	free(onelinemap);
}

void	parsemap(char *mapfile, t_cub *cub)
{
	int	fd;

	fd = openmap(mapfile);
	getconfig(fd, cub);
	getmapline(fd, cub);
	close(fd);
	makeitsquared(cub);
	checkmap(cub ->mdata.cmap, cub);
}
