NAME	:= so_long
SRC		:= so_long.c tools1.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
SRC		:= $(addprefix src/,$(SRC))
FLAGS	:= -Wall -Wextra -Werror
SRC		+= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

all: $(NAME)

$(NAME):$(SRC)
	gcc $(FLAGS) $(SRC) -Iincludes -o $@

debug:$(SRC)
	gcc -g3 -fsanitize=address $(SRC) -Iincludes -o $(NAME)

prof:$(SRC)
	gcc -pg -g3 -fsanitize=address  $(SRC) -Iincludes -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean:clean

re: clean all