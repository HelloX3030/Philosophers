CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := philo

# .h files
H_FILES := include/include.h

# .c files
vpath %.c src/

SRC_FILES := main.c

# Normal .o files
OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# includes
INCLUDES := -I include

# all
all: $(NAME)

# Link normal executable
$(NAME): $(LIBS) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

# Compile normal obj files
$(OBJ_DIR)/%.o: %.c $(H_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

# clean
clean:
	$(RM) -r $(OBJ_DIR)

# fclean
fclean:
	$(RM) -rf $(OBJ_DIR)
	$(RM) -f $(NAME)

# re
re: fclean all

# run
run: all
	./$(NAME)

.PHONY: all clean fclean re run
