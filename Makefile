NAME			:= so_long
NAME_BONUS		:= so_long_bonus
SRC				:= so_long.c tools1.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_itoa.c tools_mandatory.c
SRC_BONUS		:= so_long.c tools1.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_itoa.c tools_bonus.c
SRC				:= $(addprefix src/,$(SRC))
SRC_BONUS		:= $(addprefix src/,$(SRC_BONUS))
FLAGS			:= -Wall -Wextra -Werror -lmlx -framework OpenGl -framework AppKit
SRC				+= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 
SRC_BONUS		+= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

all: $(NAME)

$(NAME):$(SRC)
	gcc  $(FLAGS) $(SRC) -Iincludes -o $@

debug:$(SRC)
	gcc $(FLAGS) -fsanitize=address -g $(SRC) -Iincludes -o $(NAME)

prof:$(SRC)
	gcc  -pg -g3  -fsanitize=address  $(SRC) -Iincludes -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean:clean clean_bonus

re: clean all

$(NAME_BONUS):$(SRC_BONUS)
	gcc  $(FLAGS) $(SRC_BONUS) -Iincludes -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean_bonus:
	@rm -rf $(NAME_BONUS)
