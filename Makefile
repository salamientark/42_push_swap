### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = push_swap
PROJECT_DIR = ./

SRC_DIR = src
SRC_FILE = $(SRC_DIR)/math.c $(SRC_DIR)/lst_utils.c $(SRC_DIR)/init_push_swap.c \
			$(SRC_DIR)/stack.c $(SRC_DIR)/stack_sorted.c \
			$(SRC_DIR)/operation_utils.c $(SRC_DIR)/operation.c \
			$(SRC_DIR)/op_buffer_utils.c $(SRC_DIR)/op_buffer.c \
			$(SRC_DIR)/unstack_utils.c $(SRC_DIR)/unstack.c \
			$(SRC_DIR)/restack_utils.c $(SRC_DIR)/restack_optimize.c $(SRC_DIR)/restack.c\
			$(SRC_DIR)/sort_small_stack.c $(SRC_DIR)/sort_big_stack.c \
			$(SRC_DIR)/main.c
			   
			  

BONUS_DIR = push_swap_checker
BONUS_FILE = $(BONUS_DIR)/init_checker.c $(BONUS_DIR)/checker_utils.c $(BONUS_DIR)/checker.c \
				$(BONUS_DIR)/operation_utils.c $(BONUS_DIR)/operation.c $(BONUS_DIR)/main.c

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
OBJ_SRC = $(addprefix $(SRC_DIR)/, $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:.c=.o))))
OBJ_TOOLS = $(TOOLS_FILE:.c=.o)
OBJ_BONUS = $(addprefix $(BONUS_DIR)/, $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_FILE:.c=.o))))
# OBJ_TOOLS = $(TOOLS_FILE:$(TOOLS_DIR)/%.c=%.o)
# BONUS_OBJ = $(BONUS_FILE:.c=.o)

.PHONY=bonus

### RULES ###
all : $(PROJECT)

test : $(OBJ_SRC) $(OBJ_TEST)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_SRC))) \
		$(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_TOOLS))) -o $(PROJECT) $(FT_FLAG)


$(PROJECT) : $(OBJ_SRC) $(OBJ_TOOLS)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(OBJ_SRC) -o $(PROJECT) $(FT_FLAG)

$(SRC_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -g3 $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

bonus : $(OBJ_BONUS)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o checker $(FT_FLAG)

$(BONUS_DIR)/$(OBJ_DIR)/%.o : $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -I $(BONUS_DIR) -c $< -o $@
# 
# %.o : %.c
# 	$(CC) -g3 $(CFLAGS) -I $(HEADER_DIR) -c $< -o $(OBJ_DIR)/$@

fclean : clean
	rm -f $(PROJECT)
	@cd $(FT_DIR) && make fclean

#Suppresion des fichiers objet
clean :
	rm -f $(SRC_DIR)/$(OBJ_DIR)/*.o
	rm -f $(BONUS_DIR)/$(OBJ_DIR)/*.o
	@cd $(FT_DIR) && make clean

re : fclean all
