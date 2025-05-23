# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 15:26:24 by guphilip          #+#    #+#              #
#    Updated: 2025/05/23 17:01:16 by guphilip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS

BLUE				= 		\033[1;34m
GREEN				= 		\033[1;32m
YELLOW				=		\033[1;33m
CYAN				=		\033[1;36m
RESET				= 		\033[0m

# COMMANDS

RM					=		/usr/bin/rm -fr
ECHO				=		/usr/bin/echo
RM_LINE 			= 		@tput cuu1 && tput el

# FLAGS && COMPIL

CC 					= 		gcc
CFLAGS 				=		-Wall -Werror -Wextra -g
LIBFLAGS			=		-L/usr/lib -lX11 -lXext -lXrandr -lXi -lXinerama -lXcursor -lm
IFLAGS				=		-I$(INC_DIR)

# DIRECTORIES

SRC_DIR 			=		src
INC_DIR				=		includes
LIB_DIR				=		libs
OBJ_DIR				= 		build

# SO_LONG

SRC_FILES = \
	src/clean/clean_config.c \
	src/clean/clean_context.c \
	src/display/init_display.c \
	src/display/ray_casting.c \
	src/init/init_game.c \
	src/init/init_map_textures.c \
	src/init/init_parsing.c \
<<<<<<< HEAD
<<<<<<< HEAD
	src/init/init_utils.c \
=======
>>>>>>> d170c08 (~ | fix on load_walls)
=======
>>>>>>> b0d4046 (~ | jbastard <- master)
	src/inputs/camera.c \
	src/inputs/handle_inputs.c \
	src/inputs/move.c \
	src/load/load_walls.c \
=======
	src/init/init_utils.c \
	src/inputs/camera.c \
	src/inputs/handle_inputs.c \
	src/inputs/move.c \
>>>>>>> 9d54615 (+ | Walls apears, segfault w/o valgrind)
	src/main.c \
	src/parsing/config_parse_utils.c \
	src/parsing/copy_map.c \
	src/parsing/game_parse_utils.c \
	src/parsing/global_parser.c \
	src/parsing/parse_color.c \
	src/parsing/parse_config.c \
	src/parsing/parse_map.c \
	src/parsing/prepare_flood_fill.c \
	src/parsing/prepare_map_checks.c \
	src/parsing/read_map.c \
	src/parsing/validate_map_chars.c \
	src/parsing/validate_map_flood.c
OBJS				=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# MINILIBX

MLX_DIR				=		minilibx-linux
MLX_PATH			=		$(LIB_DIR)/$(MLX_DIR)
MLX_H				=		mlx.h
MLX_INC_H			=		$(INC_DIR)/$(MLX_H)
MLX_H_PATH			=		$(MLX_PATH)/$(MLX_H)
MLX_TARGET			=		libmlx.a
MLX_GIT				=		https://github.com/42Paris/minilibx-linux.git
MLX_TARGET_PATH		=		$(MLX_PATH)/$(MLX_TARGET)

#TARGET

NAME				=		cub3d
LIB_TARGET			=		$(LIBFT_TARGET) $(MLX_TARGET)

# LIBFT COMPILATION

LIBFT_GIT			= 		https://github.com/LaGuibole/Libft_Boosted.git
LIBFT_DIR			= 		Libft
LIBFT_PATH			= 		$(LIB_DIR)/$(LIBFT_DIR)
LIBFT_H				= 		libft.h
LIBFT_H_PATH		= 		$(LIBFT_PATH)/includes/$(LIBFT_H)
LIBFT_INC_H			= 		$(INC_DIR)/$(LIBFT_H)
LIBFT_TARGET		= 		libft.a
LIBFT_TARGET_PATH	= 		$(LIBFT_PATH)/$(LIBFT_TARGET)

all:						$(NAME)

fr: CFLAGS += -DLANG_FR
fr: re

clean:
							@$(RM) -r $(OBJ_DIR)

fclean: clean cleanlibs
							@$(RM) $(NAME)
							@$(RM) $(LIBFT_TARGET)
							@$(RM) $(LIBFT_INC_H)
							@$(RM) $(MLX_TARGET)
							@$(RM) $(MLX_INC_H)

re: fclean all

cleanlibs:
							@$(MAKE) clean --no-print-directory -C $(LIBFT_PATH)
							@$(MAKE) clean --no-print-directory -C $(MLX_PATH)

fcleanlibs: fclean
							@$(RM) -r $(LIBFT_PATH)
							@$(RM) -r $(MLX_PATH)

relibs: fcleanlibs $(LIBFT_INC_H) $(MLX_INC_H)

updateSources:
	@bash -c '\
		SEARCH_DIR="src"; \
		IGNORED_DIRS=("dontcopy"); \
		FIND_CMD="find $$SEARCH_DIR -type f -name '\''*.c'\''"; \
		for dir in "$${IGNORED_DIRS[@]}"; do \
			FIND_CMD+=" ! -path '\''$$SEARCH_DIR/$$dir/*'\''"; \
		done; \
		eval $$FIND_CMD | sort | awk '\''{print "\t" $$0 " \\"}'\'' \
			| sed '\''$$ s/ \\$$//'\'' > .sources_block; \
		echo "SRC_FILES = \\" > .sources_full; \
		cat .sources_block >> .sources_full; \
		awk '\'' \
			FNR==NR { lines[NR] = $$0; next } \
			/^SRC_FILES[[:space:]]*=/ { \
				print lines[1]; \
				for (i = 2; i <= length(lines); ++i) print lines[i]; \
				in_block = 1; next; \
			} \
			in_block && /^[^[:space:]]/ { in_block = 0 } \
			!in_block { print } \
		'\'' .sources_full Makefile > Makefile.tmp; \
		mv Makefile.tmp Makefile; \
		rm -f .sources_block .sources_full; \
		echo "✅ Makefile mis à jour avec les fichiers sources." \
	'


norminette:
							@norminette $(SRC_DIR) $(BONUS_SRC) $(INC_DIR) | grep -Ev '^Notice|OK!$$'	\
							&& $(ECHO) -e '\033[1;31mNorminette KO!'						\
							|| $(ECHO) -e '\033[1;32mNorminette OK!'

.PHONY: all re clean fclean cleanlibs fcleanlibs relibs norminette fr

$(LIBFT_INC_H): $(LIBFT_TARGET)
							@cp $(LIBFT_H_PATH) $@

$(LIBFT_TARGET):
							@if [ ! -d "$(LIBFT_PATH)/.git" ]; then \
								printf "Cloning lib \"%s\" into \"%s\"..." $(LIBFT_GIT) $(LIBFT_PATH);\
								git clone $(LIBFT_GIT) $(LIBFT_PATH);\
							fi
							@printf "\nMaking \"%s\"..." $@
							@$(MAKE) --no-print-directory -C $(LIBFT_PATH)
							@cp $(LIBFT_TARGET_PATH) ./
							@printf "\n✅ Done copying archive $(GREEN) \"%s\" $(RESET)... \n\n" $@

# MINILIBX COMPILATION

$(MLX_INC_H): $(MLX_TARGET)
							@cp $(MLX_H_PATH) $@

$(MLX_TARGET):
							@if [ ! -d "$(MLX_PATH)/.git" ]; then \
								printf "Cloning lib \"%s\" into \"%s\"..." $(MLX_GIT) $(MLX_PATH);\
								git clone $(MLX_GIT) $(MLX_PATH);\
							fi
							@printf "Making \"%s\"..." $@
							@$(MAKE) --no-print-directory -C $(MLX_PATH) > /dev/null 2>&1
							@printf "\n\n"
							@cp $(MLX_TARGET_PATH) ./
							@printf "✅ Done copying archive $(GREEN) \"%s\" $(RESET)... \n\n" $@

# CUB TARGET

$(NAME): $(LIBFT_INC_H) $(MLX_INC_H) $(OBJS)
							@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT_TARGET) $(MLX_TARGET) $(LIBFLAGS)
							@echo "🎉 Executable$(BLUE) $(NAME) $(RESET)created. \n"

# OBJ DIR

$(OBJ_DIR):
							@mkdir -p $(OBJ_DIR)

# .O FILE COMPILATION

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
							@echo "⚙️ Compiling $< into $@ ...\n"
							@${RM_LINE}
							@mkdir -p $(dir $@)
							@$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@
							@${RM_LINE}
