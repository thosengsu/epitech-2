##
## Makefile for arcade in /home/erwan/Tek2/C++/cpp_arcade
##
## Made by Erwan
## Login   <erwan.guiomar@epitech.eu>
##
## Started on  Fri Mar 24 17:26:18 2017 Erwan
## Last update Sun Apr  9 04:36:44 2017 Erwan
##

GAMEDIR	=	./games/

GFXDIR	=	./lib/

MENUDIR	=	./menu/

NAME	=	arcade

GREEN   =	\x1b[32;01m

WHITE   =	\x1b[0m

## COMPILE ROUTINES

games:
		@echo -e "$(GREEN)[* ~~~~~~~ Make games ~~~~~~~ *]$(WHITE)"
		cd $(GAMEDIR); make

gfx:
		@echo -e "$(GREEN)[* ~~~~~~~ Make GFX libs ~~~~~~~ *]$(WHITE)"
		cd $(GFXDIR) ; make

menu:
		@echo -e "$(GREEN)[* ~~~~~~~ Make Arcade Menu ~~~~~~~ *]$(WHITE)"
		cd $(MENUDIR) ; make

all:		$(NAME)

$(NAME):	games gfx menu


## CLEAN ROUTINES

clean:		cleanGames

cleanall:	cleanGames cleanGfx cleanMenu

cleanGames:
		@echo -e "$(GREEN)[* ~~~~~~~ Clean game dir ~~~~~~~ *]$(WHITE)"
		cd $(GAMEDIR); make clean

cleanGfx:
		@echo -e "$(GREEN)[* ~~~~~~~ Clean gfx dir ~~~~~~~ *]$(WHITE)"
		cd $(GFXDIR) ; make clean

cleanMenu:
		@echo -e "$(GREEN)[* ~~~~~~~ Clean Menu dir ~~~~~~~ *]$(WHITE)"
		cd $(MENUDIR) ; make clean

## FCLEAN ROUTINES

fclean:		fcleanGames

fcleanall:	fcleanGames fcleanGfx fcleanMenu

fcleanGames:
		@echo -e "$(GREEN)[* ~~~~~~~ Fclean game dir ~~~~~~~ *]$(WHITE)"
		cd $(GAMEDIR); make fclean

fcleanGfx:
		@echo -e "$(GREEN)[* ~~~~~~~ Fclean gfx dir ~~~~~~~ *]$(WHITE)"
		cd $(GFXDIR) ; make fclean

fcleanMenu:
		@echo -e "$(GREEN)[* ~~~~~~~ Fclean Menu dir ~~~~~~~ *]$(WHITE)"
		cd $(MENUDIR) ; make fclean

## RE ROUTINES

re:		fcleanGames games

reall:		fcleanall all

reGames:	fcleanGames games

reGfx:		fcleanGfx gfx

reMenu:		fcleanMenu menu

## OTHER

.PHONY:		all games gfx menu cleanGames cleanGfx cleanMenu fclean fcleanGame fcleanGfx fcleanMenu re reGames reGfx reMenu
