NAME = webserv
CC = c++ -I ./includes/
CC_FLAGS = -std=c++98 #-Wall -Wextra -Werror
SRCS = $(shell find src/ -type f -name "*.cpp") $(NAME).cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDES = $(shell find includes/ -type f -name "*.hpp")

all: $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp $(INCLUDES)
	$(CC) $(CC_FLAGS) -c $< -o $@

fclean: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJS)

re:fclean all

.PHONNY: all fclean re clean 