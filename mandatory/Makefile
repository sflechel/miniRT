NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIB = libft.a
LIB_DIR = libft/

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

I = -I $(INC_DIR) -I $(LIB_DIR) -I minilibx-linux
LIBS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

HEADERS_FILES =	minirt.h\
				parsing.h\
				hook.h\
				math_utils.h\
				shapes.h\

HEADERS = $(addprefix $(INC_DIR), $(HEADERS_FILES))

SRC =	hook/hook_key.c\
		hook/hook.c\
		math_utils/color_utils.c\
		math_utils/vec3_scalar_ops.c\
		math_utils/vec3_to_float_ops.c\
		math_utils/vec3_vector_ops.c\
		parsing/parse_file_and_line.c\
		parsing/parse_shape.c\
		parsing/parse_unique.c\
		parsing/parsing_utils_vector.c\
		parsing/parsing_utils.c\
		parsing/parsing.c\
		shapes/collision_shapes.c\
		shapes/collision.c\
		shapes/normals.c\
		scanning.c\
		raytracing.c\
		rotation.c\
		camera.c\
		main.c\

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: makelibft makemlx $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I) -c $< -o $@

$(NAME): $(LIB_DIR)$(LIB) minilibx-linux/libmlx_Linux.a $(OBJ_FILES) Makefile
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(I) $(LIB_DIR)$(LIB) -o $(NAME)

makelibft:
	@$(MAKE) --no-print-directory -C $(LIB_DIR)

makemlx:
	@$(MAKE) --no-print-directory -C minilibx-linux

clean:
	@$(MAKE) --no-print-directory clean -C $(LIB_DIR)
	@$(MAKE) --no-print-directory clean -C minilibx-linux
	rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) fclean --no-print-directory -C $(LIB_DIR)
	rm -f $(NAME) a.out

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re makelibft makemlx
