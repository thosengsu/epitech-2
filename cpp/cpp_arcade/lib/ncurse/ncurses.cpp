#include "ILib.hpp"
#include "ncurses.hpp"

extern "C" arcade::ILib         *create_GFX(void)
{
  return (new arcade::ncurses);
}

// int	main()
// {
//   initscr();
//   printw("Hello, world.");
//   refresh();
//   getch();
//   endwin();
//   return 0;
// }

// WINDOW *create_newwin(int height, int width, int starty, int startx)
// {	WINDOW *local_win;

// 	local_win = newwin(height, width, starty, startx);
// 	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
// 					 * for the vertical and horizontal
// 					 * lines			*/
// 	wrefresh(local_win);		/* Show that box 		*/

// 	return local_win;
// }

// void destroy_win(WINDOW *local_win)
// {	
// 	/* box(local_win, ' ', ' '); : This won't produce the desired
// 	 * result of erasing the window. It will leave it's four corners 
// 	 * and so an ugly remnant of window. 
// 	 */
// 	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
// 	/* The parameters taken are 
// 	 * 1. win: the window on which to operate
// 	 * 2. ls: character to be used for the left side of the window 
// 	 * 3. rs: character to be used for the right side of the window 
// 	 * 4. ts: character to be used for the top side of the window 
// 	 * 5. bs: character to be used for the bottom side of the window 
// 	 * 6. tl: character to be used for the top left corner of the window 
// 	 * 7. tr: character to be used for the top right corner of the window 
// 	 * 8. bl: character to be used for the bottom left corner of the window 
// 	 * 9. br: character to be used for the bottom right corner of the window
// 	 */
// 	wrefresh(local_win);
// 	delwin(local_win);
// }

// int main(int argc, char *argv[])
// {	WINDOW *my_win;
// 	int startx, starty, width, height;
// 	int ch;

// 	initscr();			/* Start curses mode 		*/
// 	cbreak();			/* Line buffering disabled, Pass on
// 					 * everty thing to me 		*/
// 	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

// 	height = 100;
// 	width = 100;
// 	starty = (LINES - height) / 2;	/* Calculating for a center placement */
// 	startx = (COLS - width) / 2;	/* of the window		*/
// 	printw("Press F1 to exit");
// 	refresh();
// 	my_win = create_newwin(height, width, starty, startx);

// 	while((ch = getch()) != KEY_F(1))
// 	{	switch(ch)
// 		{	case KEY_LEFT:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, starty,--startx);
// 				break;
// 			case KEY_RIGHT:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, starty,++startx);
// 				break;
// 			case KEY_UP:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, --starty,startx);
// 				break;
// 			case KEY_DOWN:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, ++starty,startx);
// 				break;	
// 		}
// 	}
		
// 	endwin();			/* End curses mode		  */
// 	return 0;
// }

// void print_in_middle(WINDOW *win, int starty, int startx, int width, char const *string)
// {	int length, x, y;
// 	float temp;

// 	if(win == NULL)
// 		win = stdscr;
// 	getyx(win, y, x);
// 	if(startx != 0)
// 		x = startx;
// 	if(starty != 0)
// 		y = starty;
// 	if(width == 0)
// 		width = 80;

// 	length = strlen(string);
// 	temp = (width - length)/ 2;
// 	x = startx + (int)temp;
// 	mvwprintw(win, y, x, "%s", string);
// 	refresh();
// }

// int main()
// {
//   initscr();
//   refresh();
//   if(has_colors() == FALSE)
// 	{	endwin();
// 		printf("Your terminal does not support color\n");
// 		exit(1);
// 	}
// 	start_color();			/* Start color 			*/
// 	init_pair(1, COLOR_GREEN, COLOR_GREEN);

// 	attron(COLOR_PAIR(1));
// 	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
// 	attroff(COLOR_PAIR(1));
//     	getch();
// 	endwin();
// }
