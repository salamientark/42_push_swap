### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = push_swap
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_FILE = stack.c testing_stack.c

# BONUS_FILE = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
# 			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
# 			 ft_lstmap.c

### HEADER FILE ###
HEADER_DIR = ./

# LIBFT
FT_DIR = ./libft
FT = ft

FT_FLAG = -L $(FT_DIR) -l $(FT)

## OBJECT FILE ###
OBJ_FILE = $(SRC_FILE:.c=.o)
# BONUS_OBJ = $(BONUS_FILE:.c=.o)

### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ_FILE)
	make -C $(FT_DIR)
	$(CC) -g $(CFLAGS) $(OBJ_FILE) -o $(PROJECT) $(FT_FLAG)

%.o : %.c
	$(CC) -g $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

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
