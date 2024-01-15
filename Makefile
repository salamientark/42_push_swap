### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = push_swap
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_DIR = src
SRC_FILE = $(SRC_DIR)/init_push_swap.c $(SRC_DIR)/stack.c $(SRC_DIR)/stack_utils.c \
			$(SRC_DIR)/operation.c $(SRC_DIR)/push_swap.c $(SRC_DIR)/sort_small_stack.c \
			$(SRC_DIR)/analyze_stack.c $(SRC_DIR)/op_buffer_utils.c $(SRC_DIR)/op_buffer.c \
			$(SRC_DIR)/optimize_unstack.c $(SRC_DIR)/unstack.c $(SRC_DIR)/lst_replace.c \
			$(SRC_DIR)/math.c $(SRC_DIR)/lst_join.c $(SRC_DIR)/restack.c $(SRC_DIR)/restack_optimize.c \
			main.c

# Development tools -> printing stuff
TOOLS_DIR = ./tools
TOOLS_FILE = $(TOOLS_DIR)/stack_print.c $(TOOLS_DIR)/op_buffer_print.c

# BONUS_FILE = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
# 			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
# 			 ft_lstmap.c

### HEADER FILE ###
HEADER_DIR = ./includes

# LIBFT
FT_DIR = ./libft
FT = ft
FT_FLAG = -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR = .obj
OBJ_SRC = $(SRC_FILE:.c=.o)
OBJ_TOOLS = $(TOOLS_FILE:.c=.o)
# OBJ_TOOLS = $(TOOLS_FILE:$(TOOLS_DIR)/%.c=%.o)
# BONUS_OBJ = $(BONUS_FILE:.c=.o)

### RULES ###
all : $(PROJECT)

test : $(OBJ_SRC) $(OBJ_TEST)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_SRC))) \
		$(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_TOOLS))) -o $(PROJECT) $(FT_FLAG)

$(PROJECT) : $(OBJ_SRC) $(OBJ_TOOLS)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_SRC))) \
		$(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_TOOLS))) -o $(PROJECT) $(FT_FLAG)

%.o : %.c
	$(CC) -g3 $(CFLAGS) -I $(HEADER_DIR) -c $< -o $(OBJ_DIR)/$(notdir $@)

bonus : $(BONUS_OBJ)
	ar rc $(PROJECT) $(BONUS_OBJ)

fclean : clean
	rm -f $(PROJECT)
	@cd $(FT_DIR) && make fclean

#Suppresion des fichiers objet
clean :
	rm -f *.o
	@cd $(FT_DIR) && make clean

re : fclean all
