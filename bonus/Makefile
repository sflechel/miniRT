NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIB = libft.a
LIB_DIR = libft/
clang20 = /sgoinfre/sflechel/.junest/usr/bin_wrappers/cc19

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
		math_utils/matrix.c\
		math_utils/rotation.c\
		math_utils/gradient.c\
		math_utils/projection.c\
		parsing/parse_file_and_line.c\
		parsing/parse_shape.c\
		parsing/parse_unique.c\
		parsing/parsing_utils_vector.c\
		parsing/parsing_utils_xpm.c\
		parsing/parsing_utils.c\
		parsing/parsing.c\
		parsing/alloc_lists.c\
		shapes/collision_closest_cylinder.c\
		shapes/collision_closest_shapes.c\
		shapes/collision_closest.c\
		shapes/collision_cylinder.c\
		shapes/collision_shapes.c\
		shapes/drop_shadow.c\
		shapes/texture_shape.c\
		shapes/texture_utils.c\
		shapes/normals.c\
		shapes/get_color_and_normal.c\
		free.c\
		scanning.c\
		raytracing.c\
		camera.c\
		main.c\
		errors.c\

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

fast:
	@$(MAKE) fclean
	@$(MAKE) makelibft CC=$(clang20)
	@$(MAKE) makemlx
	@$(MAKE) $(NAME) CC=$(clang20) CFLAGS="$(CFLAGS) -Wno-deprecated-non-prototype -fprofile-use=code.profdata"

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
