/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:47:59 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/05/13 13:04:29 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *s, int c);
void	gnl_strlcpy(char *dst, char *src, int size);
int		gnl_linelen(char *mem);
int		gnl_strlen(char *s);
int		lecture_master(int fd, char **time_machine);
char	*the_line_maker(char **time_machine);
char	*get_next_line(int fd);

#endif
