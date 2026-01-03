# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 19:19:07 by edelplan          #+#    #+#              #
#    Updated: 2025/02/18 17:25:15 by edelplan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_bonus = $(NAME)_bonus
SRCS =	srcs/main.c \
		srcs/exec/game_init.c \
		srcs/exec/game_loop.c \
		srcs/exec/player_movement_helper.c \
		srcs/exec/player_movement.c \
		srcs/parsing/check_empty_lines.c \
		srcs/parsing/check_map_integrity.c \
		srcs/parsing/check_textures_presence_utils.c \
		srcs/parsing/check_textures_presence.c \
		srcs/parsing/parse_textures.c \
		srcs/parsing/cub3d_utils.c \
		srcs/parsing/destroy_handler.c \
		srcs/parsing/floodfill.c \
		srcs/parsing/floodfill_helper.c \
		srcs/parsing/get_map.c \
		srcs/parsing/parse_map.c \
		srcs/render/project_walls.c \
		srcs/render/raycast_tools.c \
		srcs/render/raycast.c \
		srcs/render/render_init.c \
		srcs/render/render_tools.c \
		srcs/render/rendering.c \
		srcs/render/texture_handler.c \
		srcs/render/draw_walls.c \
		srcs/parsing/destroy_handler_utils.c \

SRCS_B = srcs_bonus/exec/check_collisions_bonus.c \
    srcs_bonus/exec/game_init_bonus.c \
    srcs_bonus/exec/game_init_helper_bonus.c \
    srcs_bonus/exec/game_loop_bonus.c \
    srcs_bonus/exec/main_bonus.c \
    srcs_bonus/exec/player_movement_bonus.c \
    srcs_bonus/exec/player_movement_helper_bonus.c \
    srcs_bonus/exec/update_doors_bonus.c \
    srcs_bonus/parsing/check_empty_lines_bonus.c \
    srcs_bonus/parsing/check_map_integrity_bonus.c \
    srcs_bonus/parsing/check_textures_presence_bonus.c \
    srcs_bonus/parsing/check_textures_presence_utils_bonus.c \
    srcs_bonus/parsing/cub3d_utils_bonus.c \
    srcs_bonus/parsing/destroy_handler_bonus.c \
    srcs_bonus/parsing/destroy_handler_helper2_bonus.c \
    srcs_bonus/parsing/destroy_handler_utils_bonus.c \
    srcs_bonus/parsing/floodfill_bonus.c \
    srcs_bonus/parsing/floodfill_helper_bonus.c \
    srcs_bonus/parsing/get_map_bonus.c \
    srcs_bonus/parsing/parse_map_bonus.c \
    srcs_bonus/parsing/parse_textures_bonus.c \
    srcs_bonus/render/animation_bonus.c \
    srcs_bonus/render/draw_walls_bonus.c \
    srcs_bonus/render/init_layers_bonus.c \
    srcs_bonus/render/minimap_bonus.c \
    srcs_bonus/render/minimap_helper_bonus.c \
    srcs_bonus/render/minimap_helper2_bonus.c \
    srcs_bonus/render/project_walls_bonus.c \
    srcs_bonus/render/raycast_bonus.c \
    srcs_bonus/render/raycast_helper_bonus.c \
    srcs_bonus/render/raycast_tools_bonus.c \
    srcs_bonus/render/render_init_bonus.c \
    srcs_bonus/render/render_tools_bonus.c \
    srcs_bonus/render/rendering_bonus.c \
    srcs_bonus/render/sprite_bonus.c \
    srcs_bonus/render/sprite_helper_bonus.c \
    srcs_bonus/render/texture_handler_bonus.c

##srcs_bonus/render/animation.c \

OBJS = ${SRCS:.c=.o}
INCLUDE = --include-directory libft
RM = rm -f
CC = cc
OBJDIR = ./objs
BONUS_CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft/include -Imlx_linux
CFLAGS = -g3 -Wall -Wextra -Werror -Iincludes -Ilibft/include -Imlx_linux
WHITE = \033[0;37m
GREEN = \033[0;32m
LIBFT = libft
MLX = ./mlx_linux
BONUS_OBJS = $(SRCS_B:.c=.o)
DOCKER_IMAGE ?= cub3d
DOCKER_MOUNT = -v "$(CURDIR)":/workspace
DOCKER_RUN = docker run --rm -it $(DOCKER_MOUNT) $(DOCKER_IMAGE)
VALGRIND ?= valgrind
VALGRIND_FLAGS ?= --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean bonus fclean re libft mlx code valgrind \
	docker-build docker-shell docker-make

all: $(NAME)
	@$(MAKE) --no-print-directory -C libft
	@$(MAKE) --no-print-directory cub3D

mlx:
	@echo "${WHITE}Compiling MiniLibX : "
	@$(MAKE) --no-print-directory -C mlx_linux
	@echo "${GREEN}MiniLibX Compiling Done!"

libft:
		@$(MAKE) --no-print-directory -C libft


$(NAME): ${OBJS}
	@make --no-print-directory mlx
	@make --no-print-directory libft
	@echo -n "${WHITE}Compiling cub3D : "
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(MLX) -lmlx -L/usr/lib -lX11 -lXext -lm -lz $(LIBFT)/libft.a
	@echo "${GREEN}Done!"
	@echo "🎮🎮🎮 CUB3D COMPILED! 🎮🎮🎮"

bonus: $(NAME_bonus)

$(NAME_bonus): $(BONUS_OBJS)
	@make --no-print-directory mlx
	@make --no-print-directory libft
	@echo -n "$(WHITE)Compiling cub3D Bonus : "
	@$(CC) $(BONUS_CFLAGS) -o $(NAME)_bonus $(BONUS_OBJS) -L$(MLX) -lmlx -L/usr/lib -lX11 -lXext -lm -lz $(LIBFT)/libft.a
	@echo "$(GREEN)Done!"
	@echo "🎮🎮🎮 CUB3D BONUS COMPILED! 🎮🎮🎮"

compile_objs: ${OBJS}

%.o: %.c
	@echo -n "${WHITE}Compiling $< : "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "${GREEN}Done!"

code :
	make re
	make clean

clean_exe:
	rm -f cub3D

clean:
	@echo -n "${WHITE}Cleaning object files : "
	@rm -f ./srcs_bonus/*.o
	@rm -f ./srcs/parsing/*.o
	@rm -f ./srcs/render/*.o
	@rm -f ./srcs/exec/*.o
	@rm -f ./srcs/*.o
	@rm -f ./srcs_bonus/*.o
	@rm -f ./srcs_bonus/parsing/*.o
	@rm -f ./srcs_bonus/render/*.o
	@rm -f ./srcs_bonus/exec/*.o
	@echo "${GREEN}Done!"
	@$(MAKE) clean --no-print-directory -C libft
	@echo "🗑️🗑️🗑️ CLEANING DONE! 🗑️🗑️🗑️"

fclean: clean
	@echo -n "${WHITE}Cleaning MiniLibX files : "
	@sleep 0.1
	@$(MAKE) clean --no-print-directory -C mlx_linux
	@echo "${GREEN}Done!"
	@make --no-print-directory -C libft fclean
	@echo -n "${WHITE}Cleaning executable files : "
	@sleep 0.1
	@${RM} cub3D
	@${RM} cub3D_bonus
	@echo "${GREEN}Done!"
	@echo "🗑️🗑️🗑️ FCLEANING DONE! 🗑️🗑️🗑️"


re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
	@echo "😎😎😎 RELINKING DONE! 😎😎😎"

valgrind: $(NAME)
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) $(VALGRIND_ARGS)

docker-build:
	@docker build -t $(DOCKER_IMAGE) .

docker-shell:
	@$(DOCKER_RUN)

docker-make:
	@$(DOCKER_RUN) bash -lc "make fclean && make"



##INCLUDE = -I . si #include <libft.h> et pas #include "libft.h"
