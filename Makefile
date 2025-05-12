NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
LIB = libft.a
LIB_DIR = libft/

SRC_DIR = src/
INC_DIR = includes/
OBJ_DIR = obj/

I = -I $(INC_DIR) -I $(LIB_DIR)

LIBS = -lreadline

HEADERS = $(INC_DIR)minishell.h $(INC_DIR)parser.h $(INC_DIR)execution.h $(INC_DIR)builtin.h

SRC =\
	core/main.c\
	core/signal.c\
	core/errors.c\
	core/env_main.c\
	core/print_structs.c\
	parser/lexer.c\
	parser/lexer_make_words.c\
	parser/grammar.c\
	parser/io.c\
	parser/io_conditions.c\
	parser/parser.c\
	parser/heredoc.c\
	parser/heredoc_signals.c\
	parser/heredoc_write.c\
	parser/expander.c\
	parser/expander_core.c\
	parser/expander_search.c\
	parser/expander_token_bigger.c\
	parser/token_utils.c\
	execution/execution.c\
	execution/execution_utils.c\
	execution/io_and_pipe.c\
	execution/builtin.c\
	execution/path.c\
	execution/signal_exec.c\
	execution/env.c\
	builtin/echo.c\
	builtin/export.c\
	builtin/env.c\
	builtin/unset.c\
	builtin/exit.c\
	builtin/pwd.c\
	builtin/cd.c\

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(SRC:.c=.o)
OBJ_FILES := $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: makelibft $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I) -c $< -o $@

$(NAME): $(LIB_DIR)$(LIB) $(OBJ_FILES) Makefile
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_DIR)$(LIB) $(LIBS) -o $(NAME)

makelibft:
	@$(MAKE) --no-print-directory -C $(LIB_DIR)

clean:
	@$(MAKE) --no-print-directory clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) fclean --no-print-directory -C $(LIB_DIR)
	rm -f $(NAME)

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

val:
	$(MAKE)
	valgrind --track-origins=yes --track-fds=yes --quiet --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re makelibft val
