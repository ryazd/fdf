NAME = fdf

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lmlx -lft -L$(LIB_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIB_HEADERS) -I$(MINILIBX_HEADERS)

LIB = $(LIB_DIRECTORY)libft.a
LIB_DIRECTORY = ./includes/libft/
LIB_HEADERS = $(LIB_DIRECTORY)includes/

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./includes/minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = fdf.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST =  fdf.c             \
                fdf1.c            \
                get_next_line.c   \
                ft_split.c        \
				coord.c           \
				ft_free.c         \

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)

CREAT = \033[0;32m
IMPORTANT =\033[1;36m
DELETE = \033[0;31m
EOC = \033[0m

$(NAME): $(LIB) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(IMPORTANT)<----- Fdf sucсessfully created ---->$(EOC)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(CREAT)<----- Object directory was created ----->$(EOC)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CREAT)<----- Objects were created ------ ------>$(EOC)"

$(LIB):
	@$(MAKE) -sC $(LIB_DIRECTORY)
	@echo "$(CREAT)<----- Libft was created ------ --->$(EOC)"

$(MINILIBX):
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)
	@echo "$(CREAT)<----- MinilibX was created ------ ------>$(EOC)"

clean:
	@$(MAKE) -sC $(LIB_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(DELETE)<----- All objects were deleted ------ -->$(EOC)"

fclean: clean
	@rm -f $(MINILIBX)
	@rm -f $(LIB)
	@rm -f $(NAME)
	@echo "$(DELETE)<----- All files were deleted ------ ---->$(EOC)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(IMPORTANT)<----- All files were rebuild ----->$(EOC)"

.PHONY: all clean fclean re
