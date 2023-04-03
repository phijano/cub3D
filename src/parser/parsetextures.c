/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:17:21 by ntamayo-          #+#    #+#             */
/*   Updated: 2023/03/13 20:21:02 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static int	texlen(char *line)
{
	int	ret;

	ret = 0;
	while (line[ret] > 32 && line[ret] < 127)
		ret++;
	return (ret);
}

static char	**gettexptr(char *line, t_cub *cub)
{
	char	**texturedir;

	texturedir = NULL;
	if (!cub->mdata.npath && !ft_strncmp(line, "NO", 2))
		texturedir = &cub->mdata.npath;
	else if (!cub->mdata.spath && !ft_strncmp(line, "SO", 2))
		texturedir = &cub->mdata.spath;
	else if (!cub->mdata.wpath && !ft_strncmp(line, "WE", 2))
		texturedir = &cub->mdata.wpath;
	else if (!cub->mdata.epath && !ft_strncmp(line, "EA", 2))
		texturedir = &cub->mdata.epath;
	else if (ft_strncmp(line, "F", 1) && ft_strncmp(line, "C", 1))
		frerrxit("Bad/dup texture identifier. Accepted: [NO, WE, SO, EA]", cub);
	return (texturedir);
}

static int	texstore(char *line, t_cub *cub)
{
	char	**texturedir;
	int		len;

	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (0);
	texturedir = gettexptr(line, cub);
	if (!texturedir)
		return (1);
	line += 2;
	while (ft_isspace(*line))
		line++;
	len = texlen(line);
	if (!len)
		frerrxit("Missing texture path.", cub);
	*texturedir = ft_substr(line, 0, len);
	if (!*texturedir)
		frerrxit("Failed to copy a texture path.", cub);
	while (line[len])
		if (!ft_isspace(line[len++]))
			frerrxit("Trailing bad stuff in texture declaration.", cub);
	return (0);
}

int	gettextures(char *line, t_cub *cub)
{
	return (texstore(line, cub));
}
