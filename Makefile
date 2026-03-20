# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:09:02 by sancuta           #+#    #+#              #
#    Updated: 2026/03/20 11:01:39 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
SRCS =	main.c \
		ft_print_memory.c \
		parsing.c \
		arena/arena_alloc_reset.c \
		arena/arena_init_free.c \
		arena/arena_save_restore.c \
		arena/arena_strings.c \
		executing.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: .release $(NAME)

.release:
	if [ -f .debug ]; then $(MAKE) fclean; fi
	touch .release

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT): FORCE
	if [ -f .debug ]; then $(MAKE) -C libft debug; \
	else $(MAKE) -C libft; fi

FORCE:

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) .debug .release

re: fclean all

debug: CFLAGS += -g #-fsanitize=address,leak,undefined
debug: .debug $(NAME)

.debug:
	if [ -f .release ]; then $(MAKE) fclean; fi
	touch .debug

.PHONY: all clean fclean re debug FORCE

-include $(DEPS)
