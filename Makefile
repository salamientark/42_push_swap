### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = push_swap
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_FILE = arg_parser.c stack.c main.c operation.c

# Development tools -> printing stuff
TOOLS_DIR = ./tools
TOOLS_FILE = $(TOOLS_DIR)/stack_print.c

# BONUS_FILE = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
# 			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
# 			 ft_lstmap.c

### HEADER FILE ###
HEADER_DIR = ./includes

# LIBFT
FT_DIR = ./libft
FT = ft

FT_FLAG = -L $(FT_DIR) -l $(FT)

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
	$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_SRC)) \
		$(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_TOOLS))) -o $(PROJECT) $(FT_FLAG)

$(PROJECT) : $(OBJ_SRC) $(OBJ_TOOLS)
	make -C $(FT_DIR)
	$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_SRC)) \
		$(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_TOOLS))) -o $(PROJECT) $(FT_FLAG)

%.o : %.c
	$(CC) -g $(CFLAGS) -I $(HEADER_DIR) -c $< -o $(OBJ_DIR)/$(notdir $@)

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
