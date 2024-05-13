#gcc so_long.c map.c check_map.c MLX42/libmlx42.a libft/libft.a -Iinclude -lglfw -L "/Users/anttorre/.brew/opt/glfw/lib/" -o so_long
#gcc so_long.c map.c check_map.c MLX42/libmlx42.a libft/libft.a -Iinclude -ldl -lglfw -pthread -lm -o so_long

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME = cub3D

#NAME_BONUS = 

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

MLX_PATH = ./MLX42

MLX = $(MLX_PATH)/libmlx42.a

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

LIB_NAME = cub3D.a

#LIB_NAME_BONUS = 

LIB = ar rcs

#LIB_SYS = -Iinclude -ldl -lglfw -pthread -lm

LIB_SYS = -lm -Iinclude -lglfw -L "/Users/anttorre/.brew/opt/glfw/lib/"

SRCS = 	src/check_map.c \
		src/cub3d.c \
		src/errors.c \
		src/free.c \
		src/game.c \
		src/keypress.c \
		src/parser.c \
		src/raycast.c \
		src/rendering.c \
		src/start_map.c \

OBJS = $(SRCS:.c=.o)

$(NAME) :	$(OBJS) $(LIBFT) $(MLX)
			@echo "$(MAGENTA)$(BOLD)Compiling Cub3D...$(RESET)"
			@$(LIB) $(LIB_NAME) $(OBJS)
			@$(CC) $(CFLAGS) $(LIB_NAME) $(MLX) $(LIBFT) -Iinclude/cub3d.h $(LIB_SYS) -o $(NAME)
			@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(OBJS):	src/%.o : src/%.c 
			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
			@make -s -C $(LIBFT_PATH)
			@make bonus -s -C $(LIBFT_PATH)

$(MLX):
			@make -s -C $(MLX_PATH)

all : $(NAME)

bonus : $(NAME_BONUS)

clean:
			@echo "$(RED)$(BOLD)Cleaning objects from Cub3D...$(RESET)"
			@rm -f $(OBJS) $(OBJS_BONUS)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make clean -s -C $(MLX_PATH)
			@make clean -s -C $(LIBFT_PATH)

fclean:
			@echo "$(RED)$(BOLD)Cleaning all files from Cub3D...$(RESET)"
			@rm -f $(NAME) $(NAME_BONUS) $(OBJS) $(OBJS_BONUS) $(LIB_NAME) $(LIB_NAME_BONUS) $(LIBFT) $(MLX)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make fclean -s -C $(MLX_PATH)
			@make fclean -s -C $(LIBFT_PATH)

re : fclean all

cub : all clean

.PHONY : all re fclean clean bonus cub