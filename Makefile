NAME		:= minishell
LIBFT		:= libft
SRC_DIR		:= src/
OBJ_DIR		:= obj/
INCLUDES	:= -I ./include -I $(LIBFT)/include -I /Users/$(USER)/.brew/opt/readline/include
READL_FLAGS	:= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
CC			:= cc

ifdef WITH_DEBUG
CFLAGS		:= -fsanitize=address -g
else
CFLAGS		:= -Wall -Werror -Wextra
endif

# Reset
NC		:= \033[0m# 		Text Reset

# Regular Colors
BLACK	:= \033[0;30m#	Black
RED		:= \033[3;31m#	Red
GREEN	:= \033[3;32m#	Green
BLD_GRN	:= \033[1;32m#	Green
YELLOW	:= \033[3;33m#	Yellow
BLUE	:= \033[1;34m#	Blue
PURPLE	:= \033[3;35m#	Purple
BLD_PUR	:= \033[1;35m#	Purple but bold
CYAN	:= \033[3;36m#	Cyan
WHITE	:= \033[1;37m#	White

EXECUTION		:= execution/
EXEC_FILES		:= $(EXECUTION)executer.c $(EXECUTION)guillotine.c $(EXECUTION)ms_execvp.c \
				   $(EXECUTION)exec_cmd.c $(EXECUTION)executer_utils.c $(EXECUTION)fd_utils.c

BUILTIN			:= builtin/
BUILTIN_FILES	:= $(BUILTIN)cd.c $(BUILTIN)echo.c $(BUILTIN)env.c $(BUILTIN)exit.c \
				   $(BUILTIN)export.c $(BUILTIN)pwd.c $(BUILTIN)unset.c $(BUILTIN)utils.c \
				   $(BUILTIN)exit_utils.c

TOKENIZER		:= tokenizer/
TOKENIZER_FILES	:= $(TOKENIZER)tokenize.c $(TOKENIZER)parsetokens.c $(TOKENIZER)parse.c $(TOKENIZER)handle_word.c \
				   $(TOKENIZER)handle_operator.c $(TOKENIZER)ft_lexer.c $(TOKENIZER)other_length.c $(TOKENIZER)precheck.c

EXPANDER		:= expander/
EXPANDER_FILES	:= $(EXPANDER)expander.c $(EXPANDER)expander_utils.c $(EXPANDER)check_expansion.c $(EXPANDER)countsubstr.c \
				   $(EXPANDER)find_needles.c $(EXPANDER)get_cwd_size.c $(EXPANDER)removequotes.c $(EXPANDER)resize.c \
				   $(EXPANDER)wildcard.c $(EXPANDER)wildcardsplit.c $(EXPANDER)splitargs.c $(EXPANDER)emptycheck.c 

MISC 			:= misc/
MISC_FILES		:= $(MISC)here_doc.c $(MISC)cmd_functions.c $(MISC)clear_functions.c $(MISC)ft_mini_env.c \
				   $(MISC)branch_functions.c $(MISC)inthandlers.c $(MISC)skipquotes.c

SRC_FILES		:= main.c $(EXEC_FILES) $(BUILTIN_FILES) $(TOKENIZER_FILES) $(EXPANDER_FILES) $(MISC_FILES)
SRCS			:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS			:= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(GREEN)compiling:$(NC)" $^
	@$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)creating folders...$(NC)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(EXECUTION)
	@mkdir -p $(OBJ_DIR)$(TOKENIZER)
	@mkdir -p $(OBJ_DIR)$(EXPANDER)
	@mkdir -p $(OBJ_DIR)$(BUILTIN)
	@mkdir -p $(OBJ_DIR)$(MISC)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(PURPLE)============================[$(BLD_PUR)$(LIBFT)$(NC)$(PURPLE)]============================$(NC)"
	@$(MAKE) -C $(LIBFT)
	@echo "$(PURPLE)============================[$(BLD_PUR)$(NAME)$(NC)$(PURPLE)]============================$(NC)"
	@echo "$(GREEN)creating $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(READL_FLAGS) $(LIBFT)/libft.a -o $@
	@echo "$(BLD_GRN)done!$(NC)"

debug:
	@$(MAKE) WITH_DEBUG=1 all

clean:
	@echo "$(CYAN)cleaning...$(NC)"
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIBFT)/libft.a
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean debug fclean re
