##
## Makefile<snake> for arcade in /home/erwan/Tek2/C++/cpp_arcade
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Apr  9 18:23:35 2017 Erwan
## Last update Sun Apr  9 18:23:37 2017 Erwan
##

NAME_SNAKE	=	snake.so

CC		=	g++

RM		=	rm -f

CPPFLAGS	+=	-Werror -Wall -Wextra -I../../includes/ -I../  -I../../dlLoader/
CPPFLAGS	+=	-I../../lib/ -fPIC

LDFLAGS		+=	-Wl,--no-undefined -lm -ldl -lpthread -lrt -shared

SRCS_SNAKE	=	snake.cpp \
			./../../dlLoader/dlGfxLoader.cpp

OBJS_SNAKE	=	$(SRCS_SNAKE:.cpp=.o)

all: $(NAME_SNAKE)

$(NAME_SNAKE): $(OBJS_SNAKE)
	$(CC) -o $(NAME_SNAKE) $(OBJS_SNAKE) $(LDFLAGS)
	cp $(NAME_SNAKE) ../$(NAME_SNAKE)

clean:
	$(RM) $(OBJS_SNAKE)

fclean: clean
	$(RM) $(NAME_SNAKE)
	$(RM) ../$(NAME_SNAKE)

re: fclean all
