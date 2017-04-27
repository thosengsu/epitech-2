##
## Makefile for philosopher in /home/tomlenor/Documents/Tek2/PSU_2016_philo
##
## Made by tomlenor
## Login   <tom.lenormand@epitech.eu>
##
## Started on  Tue Mar  7 11:55:03 2017 tomlenor
## Last update Mon Mar 13 09:56:40 2017 Erwan
##

NAME		=	philo

CC		=	gcc

RM		=	rm -rf

CFLAGS		+=	-Wall -Werror -Wextra -IlibRice/ -Iincludes/

LDFLAGS		+=	-L./libRice/ -lriceferee -lpthread

SRCS		=	src/main.c \
			src/checks.c \
			src/actions.c

OBJS		=	$(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
