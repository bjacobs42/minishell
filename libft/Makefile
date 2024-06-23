NAME		= libft.a
SRC_FR		= src/
OBJ_FR		= obj/
INCLUDES	= ./include
CFLAGS		= -g -Wall -Werror -Wextra -I
CC			= cc

# Reset
NC		= \033[0m# 		Text Reset

# Regular Colors
BLACK	= \033[0;30m#	Black
RED		= \033[3;31m#	Red
GREEN	= \033[3;32m#	Green
BLD_GRN	= \033[1;32m#	Green
YELLOW	= \033[3;33m#	Yellow
BLUE	= \033[1;34m#	Blue
PURPLE	= \033[3;35m#	Purple
BLD_PUR	= \033[1;35m#	Purple but bold
CYAN	= \033[3;36m#	Cyan
WHITE	= \033[1;37m#	White

FTIS_FR		= ft_is/
FTIS		= ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace

FTTO_FR		= ft_to/
FTTO		= ft_atoi ft_itoa ft_tolower ft_toupper ft_ltou ft_btoa ft_atoh ft_atob

FTSTR_FR	= ft_str/
FTSTR		= ft_split ft_strdup ft_strjoin ft_strlcpy ft_strmapi ft_strnstr ft_strtrim ft_strchr \
		  ft_striteri ft_strlcat ft_strlen ft_strncmp ft_strrchr ft_substr ft_strarr_size

FTPUT_FR	= ft_put/
FTPUT		= ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTMEM_FR	= ft_mem/
FTMEM		= ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_memswap \
			  ft_swap ft_realloc ft_random

FTLST_FR	= ft_lst/
FTLST		= ft_lstadd_back ft_lstclear ft_lstiter ft_lstmap ft_lstsize ft_lstadd_front \
		  ft_lstdelone ft_lstlast ft_lstnew ft_lstsort_alpha

FTCLEAR_FR	= ft_clear/
FTCLEAR	= ft_clear_arr ft_clear_strarr

FTPRINTF_FR	= ft_printf/
FTPRINTF	= print_args print_p ft_printf_fd

SRC_FILES	+= $(addprefix $(FTIS_FR),$(FTIS))
SRC_FILES	+= $(addprefix $(FTTO_FR),$(FTTO))
SRC_FILES	+= $(addprefix $(FTSTR_FR),$(FTSTR))
SRC_FILES	+= $(addprefix $(FTPUT_FR),$(FTPUT))
SRC_FILES	+= $(addprefix $(FTMEM_FR),$(FTMEM))
SRC_FILES	+= $(addprefix $(FTLST_FR),$(FTLST))
SRC_FILES	+= $(addprefix $(FTPRINTF_FR),$(FTPRINTF))
SRC_FILES	+= $(addprefix $(FTCLEAR_FR),$(FTCLEAR))

SRCS		= $(addprefix $(SRC_FR), $(addsuffix .c, $(SRC_FILES)))
OBJS		= $(addprefix $(OBJ_FR), $(addsuffix .o, $(SRC_FILES)))

all:  ${OBJ_FR} ${NAME}

$(OBJ_FR)%.o : ${SRC_FR}%.c
	@echo "$(GREEN)compiling:$(NC)" $^
	@${CC} ${CFLAGS} $(INCLUDES) -c $^ -o $@

$(OBJ_FR):
	@echo "$(YELLOW)creating folders...$(NC)"
	@mkdir -p $(OBJ_FR)
	@mkdir -p $(OBJ_FR)$(FTIS_FR)
	@mkdir -p $(OBJ_FR)$(FTTO_FR)
	@mkdir -p $(OBJ_FR)$(FTSTR_FR)
	@mkdir -p $(OBJ_FR)$(FTPUT_FR)
	@mkdir -p $(OBJ_FR)$(FTMEM_FR)
	@mkdir -p $(OBJ_FR)$(FTLST_FR)
	@mkdir -p $(OBJ_FR)$(FTCLEAR_FR)
	@mkdir -p $(OBJ_FR)$(FTPRINTF_FR)

$(NAME): ${OBJ_FR} ${OBJS}
	@echo "$(GREEN)creating $@...$(NC)"
	@ar rcs $@ ${OBJS}
	@echo "$(BLD_GRN)done!$(NC)"

clean:
	@rm -rf ${OBJ_FR}
fclean: clean
	@rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re
