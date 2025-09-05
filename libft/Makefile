# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yihssan  <yihssan @student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 21:54:30 by yihssan           #+#    #+#              #
#    Updated: 2021/05/31 23:58:00 by yihssan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c ft_strchr_s.c ft_strndup.c get_next_line.c \
	ft_printf/srcs/config_output.c ft_printf/srcs/ft_chardup.c \
	ft_printf/srcs/ft_printf.c ft_printf/srcs/ft_ptoxa.c \
	ft_printf/srcs/ft_strndup.c ft_printf/srcs/ft_uitoa.c \
	ft_printf/srcs/ft_uitoxa.c ft_printf/srcs/prc_width_utils.c \
	ft_printf/srcs/set_struct.c ft_printf/srcs/utils.c
OBJS = $(SRC:%.c=%.o)
INC = libft.h
BON = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
	ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
BON_OBJS = $(BON:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	/bin/rm -f $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

bonus: $(BON_OBJS)
	ar rcs $(NAME) $(BON_OBJS)
	/bin/rm -f $(BON_OBJS)

clean:
	/bin/rm -f $(OBJS) $(BON_OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re