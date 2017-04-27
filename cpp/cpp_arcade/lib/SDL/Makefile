##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Apr  9 18:24:15 2017 Erwan
## Last update Sun Apr  9 18:26:04 2017 Erwan
##

NAME		=	lib_arcade_sdl.so

RM		=	rm -f

CC		=	g++

CPPFLAGS	+=	-Wall -Werror -Wextra -e3 -fPIC -I/usr/include/SDL2 -I../ -D_REENTRANT -g3

LDFLAGS		+=	-shared -L/usr/lib -lSDL2 -L/usr/lib -lSDL2 -Wl,--no-undefined -lm
LDFLAGS		+=	-ldl -lpthread -lrt -lSDL2_ttf -lSDL2_image

SRCS		=	SDL.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
	cp $(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all
