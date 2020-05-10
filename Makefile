# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 11:50:11 by kdeloise          #+#    #+#              #
#    Updated: 2020/05/10 15:27:45 by kdeloise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem_in

CFLAGS 	= -Wall -Wextra -Werror

SRC1 	= additional.c bfs.c bubble_sort.c change_graph.c\
			check_dbl_create_arr_rooms.c check_secc.c check_steps.c\
			collision_handle.c create_links.c create_rooms.c fill_buf.c\
			free_func.c is_seclc.c lem_in.c output.c plist_push_back.c\
			queue.c quick_sort.c suurbale.c util.c validation.c

OBJD 	= temporary

OBJ 	= $(addprefix $(OBJD)/,$(SRC1:.c=.o))

HDR 		= -I./

LIBFT_HDR 	= -I./libft

LIB_BINARY	= -L./libft -lft

LIBFT		= ./libft/libftprintf.a

all: $(LIBFT) ./libft/libftprintf.a $(NAME)

FORCE:		;

LIBFT		= ./libft/libftprintf.a

$(LIBFT):	FORCE
			make -C ./libft

$(OBJD):
	mkdir $@

$(OBJD)/%.o: %.c | $(OBJD)
	gcc -g $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) ./lem_in.h
	gcc -g $(OBJ) $(LIBFT) -o $@

clean:
	/bin/rm -rf $(OBJ)
	rm -rf $(OBJD)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all