/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:49:42 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/06/18 19:42:02 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	lecture_master(int fd, char **time_machine)
{
	int		eoflag;
	char	buffer[BUFFER_SIZE + 1];

	if (!*time_machine)
	{
		*time_machine = malloc(sizeof(char));
		if (!*time_machine)
			return (-1);
		**time_machine = 0;
	}
	eoflag = 1;
	while (!gnl_strchr(*time_machine, '\n') && eoflag)
	{
		eoflag = read(fd, buffer, BUFFER_SIZE);
		if (eoflag < 1)
			return (eoflag);
		buffer[eoflag] = 0;
		*time_machine = gnl_strjoin(*time_machine, buffer);
	}
	return (eoflag);
}

char	*the_line_maker(char **time_machine)
{
	int		len;
	int		temporal_distortion;
	char	*tmach2;
	char	*retline;

	len = gnl_linelen(*time_machine);
	if (!len)
		return (NULL);
	retline = malloc(sizeof(char) * (len + 1));
	if (!retline)
		return (NULL);
	gnl_strlcpy(retline, *time_machine, len);
	temporal_distortion = gnl_strlen(&time_machine[0][len]);
	tmach2 = malloc(sizeof(char) * (temporal_distortion + 1));
	if (!tmach2)
		return (NULL);
	gnl_strlcpy(tmach2, &time_machine[0][len], temporal_distortion);
	free(*time_machine);
	*time_machine = tmach2;
	return (retline);
}

char	*get_next_line(int fd)
{
	static char	*time_machine[4096] = {0};
	char		*ret;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(time_machine[fd]);
		time_machine[fd] = NULL;
		return (NULL);
	}
	if (lecture_master(fd, &time_machine[fd]) < 0)
	{
		free(time_machine[fd]);
		time_machine[fd] = NULL;
		return (NULL);
	}
	ret = the_line_maker(&time_machine[fd]);
	if (!ret)
	{
		free(time_machine[fd]);
		time_machine[fd] = NULL;
	}
	return (ret);
}
