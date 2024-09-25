NAME := RPN
SRCS := $(shell find -type f -name "*.cpp")
OBJS := $(SRCS:.cpp=.o)
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98 -pedantic

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
