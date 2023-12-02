NAME = fractol

SRC_PATH = srcs

SRC = main.c

SRC := $(addprefix $(SRC_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CC = clang

INCLUDES = -I minilibx-linux/ -I./ -Ilibft/

LBS = -L ./minilibx-linux/ -lmlx -lX11 -lXext

CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

RM = rm -f

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME)

$(LIBFT) :
	make bonus -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) ${OBJ} $(NAME).h
	$(CC) $(INCLUDES) -o $(NAME) $(SRC) $(LBS) $(LIBFT)

bonus : $(NAME)

clean :
	make clean -C $(LIBFT_PATH)
	$(RM) $(NAME) $(OBJ)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

c :
	make -C $(LIBFT_PATH)
	${CC} -g3 -Ilibft $(SRC) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re
