# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 18:48:04 by ntamayo-          #+#    #+#              #
#    Updated: 2023/03/10 12:49:43 by senari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libft.a

CFLAGS		=	-Wall -Werror -Wextra

VPATH		=	./:./get_next_line

################################################################################

SRC			= ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c\
			  ft_strlen.c ft_memset.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
			  ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c\
			  ft_itoa.c ft_bzero.c ft_calloc.c ft_strdup.c ft_substr.c\
			  ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c\
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS_SRC	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
			  ft_lstmap.c

EXTRA_SRC	= ft_abs.c ft_ipow.c ft_free.c ft_ioverflw.c ft_isspace.c

GNL_SRC		= $(addprefix ./get_next_line/, get_next_line_bonus.c get_next_line_utils_bonus.c)


LIBSRCS		= $(SRC) $(BONUS_SRC) $(EXTRA_SRC) $(GNL_SRC)

################################################################################

OBJS		= $(SRC:.c=.o)

BONUS_OBJS	= $(BONUS_SRC:.c=.o)

EXTRA_OBJS	= $(EXTRA_SRC:.c=.o)

GNL_OBJS	= $(addsuffix .o, $(notdir $(basename $(GNL_SRC))))


LIBOBJS		= $(OBJS) $(BONUS_OBJS) $(EXTRA_OBJS) $(GNL_OBJS)

################################################################################

all:		$(NAME)

$(NAME):	$(LIBOBJS)
	@echo -n ' >'
	@ar rcs $(NAME) $(LIBOBJS)

%.o:		%.c
	@echo -n '>'
	@gcc $(CFLAGS) -c $<

clean:
	@rm -f $(LIBOBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
