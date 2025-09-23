############################## Colors #########################################

BLEU := \033[36m
PURPLE := \033[35m
GREEN := \033[32m
RED := \033[31m
RESET := \033[0m
ERASE := \033[2K\033[1A\r

############################## Variables #######################################

DIR_OBJS := .objs

OBJS =	$(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))

NAME = ft_nm

INC_DIR =	include

FLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -g3

SRCS =	main.c \
		ft_nm.c \
		64bits.c \
		32bits.c \
		sort.c \
		utils.c \
		libft.c

############################## Rules ##########################################

all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)
	echo "$(GREEN)✅ $(NAME) compilated !"

$(DIR_OBJS)/%.o: src/%.c Makefile
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	gcc $(FLAGS) -MMD -c $< -o $@
	sleep 0.1
	printf "$(ERASE)"

$(DIR_OBJS):
	mkdir -p $@

run: all
	./$(NAME) -ra .objs/32bits.o tests/cub3D tests/ft_nm as tests/32bits.o > mine ; nm -ra .objs/32bits.o tests/cub3D tests/ft_nm as tests/32bits.o > true ; diff mine true

clean:
	echo "$(PURPLE)🧹Removing $(NAME).o files !"
	rm -rf $(DIR_OBJS)

fclean: clean
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re all

.SILENT:
