### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = libftprintf.a
PROJECT_DIR = ./

### SOURCE FILES ###
SRC = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

### HEADER FILE ###
HEADER_DIR = ./
#HEADER_FILE = ft_printf.h
## OBJECT FILE ###
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

# SELECTOR 
#  Change this variable to select default get_next_line


### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ)
	ar rc $(PROJECT) $(OBJ)

%.o : %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

bonus : $ all

fclean : clean
	rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	rm -f *.o

re : fclean all