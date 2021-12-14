NAME	:= so_long
SRC		:= so_long.c
SRC		:= $(addprefix src/,$(SRC))
FLAGS	:= -Wall -Wextra -Werror

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