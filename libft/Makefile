NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = ./
INC_DIR = ./

HEADERS = $(INC_DIR)libft.h\

SRC_FILES = $(SRC_DIR)ft_isalpha.c\
		$(SRC_DIR)ft_is2.c\
		$(SRC_DIR)ft_str.c\
		$(SRC_DIR)ft_str2.c\
	    $(SRC_DIR)ft_mem.c\
	    $(SRC_DIR)ft_misc.c\
	    $(SRC_DIR)ft_malloced.c\
	    $(SRC_DIR)ft_split.c\
	    $(SRC_DIR)ft_itoa.c\
	    $(SRC_DIR)ft_striteri.c\
	    $(SRC_DIR)ft_put.c\
		$(SRC_DIR)ft_lst_bonus.c\
		$(SRC_DIR)ft_lst2_bonus.c\
		$(SRC_DIR)ft_dprintf.c\
		$(SRC_DIR)ft_dprintft1.c\
		$(SRC_DIR)ft_dprintfutils.c\
		$(SRC_DIR)get_next_line.c\
		$(SRC_DIR)ft_realloc.c\
		$(SRC_DIR)ft_atoi.c\
		$(SRC_DIR)dynamic_array.c\
		$(SRC_DIR)hash_map_methods.c\
		$(SRC_DIR)hash_map.c\
		$(SRC_DIR)hash_map_utils.c\
		$(SRC_DIR)ft_quicksort.c\
		$(SRC_DIR)str_triple_join.c\
		$(SRC_DIR)multifree.c\
		$(SRC_DIR)multifree_return_null.c\
		$(SRC_DIR)multifree_return_one.c\
		$(SRC_DIR)multifree_return_zero.c\
		$(SRC_DIR)strchr_index.c\
		$(SRC_DIR)safe_atoi.c\
#		$(SRC_DIR)main.c\

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(OBJ_FILES): %.o:%.c $(HEADERS)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES) Makefile
		  ar rcs $(NAME) $(OBJ_FILES)

clean:
	rm -rf $(OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	rm -f $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re test
