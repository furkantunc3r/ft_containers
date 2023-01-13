APP		= ft_containers
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
MFILES	= $(wildcard ./*.cpp)

all		:  run

run		:
	$(CC) -o $(APP) $(CFLAGS) $(MFILES)

clean	:
	@rm -rf $(APP)

re : fclean all

.PHONY: all run clean fclean re