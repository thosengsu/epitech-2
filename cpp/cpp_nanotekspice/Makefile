##
## Makefile for nanoTekSpice in /home/erwan/Tek2/C++/cpp_nanotekspice
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Sun Mar  5 01:51:13 2017 Erwan
## Last update Sun Mar  5 17:12:59 2017 Erwan
##

NAME		=	nanotekspice

LIBNAME		=	libnanotekspice.a

CC		=	g++

RM		=	rm -f

CPPFLAGS	+=	-Wall -Wextra -Werror -std=c++14 -Iinclude/

LIBFLAGS	=	-L./ -lnanotekspice

SRCSDIR		=	./src

SRCS		=	$(SRCSDIR)/AComponent.cc \
			$(SRCSDIR)/Agates.cc \
			$(SRCSDIR)/andGate.cc \
			$(SRCSDIR)/checkArg.cc \
			$(SRCSDIR)/comp4001.cc \
			$(SRCSDIR)/comp4011.cc \
			$(SRCSDIR)/comp4030.cc \
			$(SRCSDIR)/comp4069.cc \
			$(SRCSDIR)/comp4071.cc \
			$(SRCSDIR)/comp4081.cc \
			$(SRCSDIR)/exOrGate.cc \
			$(SRCSDIR)/In.cc \
			$(SRCSDIR)/invertGate.cc \
			$(SRCSDIR)/nandGate.cc \
			$(SRCSDIR)/norGate.cc \
			$(SRCSDIR)/orGate.cc \
			$(SRCSDIR)/Out.cc \
			$(SRCSDIR)/Parser.cc \
			$(SRCSDIR)/readFile.cc \
			$(SRCSDIR)/shell.cc \
			$(SRCSDIR)/tekSpice.cc

OBJS		=	$(SRCS:.cc=.o)

MAINSRCS	=	$(SRCSDIR)/main.cc

MAINOBJ		=	$(MAINSRCS:.cc=.o)


all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar cr $(LIBNAME) $(OBJS)
	ranlib $(LIBNAME)

$(NAME): $(MAINOBJ) $(LIBNAME)
	$(CC) -o $(NAME) $(MAINOBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(MAINOBJ)


fclean: clean
	$(RM) $(LIBNAME)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME) $(LIBNAME)
