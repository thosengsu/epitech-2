#ifndef NCURSE_HPP
# define NCURSE_HPP

# include <iostream>
# include <stdexcept>
# include <map>
# include <string>
# include <functional>
# include <ncurses_dll.h>
# include <ncurses.h>
# include <fstream>
# include <sys/ioctl.h>
# include "ILib.hpp"

namespace arcade
{
  class ncurses : public ILib
  {
  private :
    std::map<std::string, char>				_sprite;
    std::map<int, std::function<void (void *)>>		_cmd;

  public :
    /* ------------ */
    /* CTOR && DTOR */
    /* ------------ */
    ncurses() {};

    virtual ~ncurses() {};

    /* ------------ */
    /* MEMBERS FCTS */
    /* ------------ */

    virtual void		init(const std::string&)
    {
      if (initscr() == NULL || keypad(stdscr, TRUE) == ERR || nodelay(stdscr, TRUE) || noecho() == ERR ||
	  curs_set(0) == ERR || clear() == ERR || start_color() == ERR)
	{
	  this->close();
	  throw (std::runtime_error("Init Crashed"));
	}
      init_pair(0, COLOR_YELLOW, COLOR_YELLOW);
      init_pair(1, COLOR_RED, COLOR_RED);
      init_pair(2, COLOR_BLUE, COLOR_BLUE);
      init_pair(3, COLOR_CYAN, COLOR_CYAN);
      init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
      init_pair(5, COLOR_BLACK, COLOR_BLACK);
    }

    virtual void		close(void)
    {
      if (curs_set(1) == ERR || nodelay(stdscr, FALSE) == ERR ||
	  keypad(stdscr, FALSE) == ERR || echo() == ERR || endwin() == ERR)
	throw (std::runtime_error("Failed to close ncurses variables"));
    }

    virtual void		loadSprite(const std::string &name, const std::string &filename)
    {
      std::ifstream	file;
      std::string	line;
      std::string	fileName(filename);
      int		nb;

      auto		idx = fileName.find(".png");
      fileName.replace(idx, 4, ".txt");

      file.open(fileName.c_str());
      if (file.is_open())
	{
	  std::getline(file, line);
	  if ((line[0] < '1' && line[0] > '5') && line[1] != '\0')
	    {
	      this->close();
	      throw (std::runtime_error("failled to parse the .txt for Ncurses"));
	    }
	  nb = std::stoi(line);
	  this->_sprite[name] = nb;
	}
      else
	{
	  this->close();
	  throw (std::runtime_error("couldn't open ncurses color text file"));
	}
      file.close();
    }

    virtual void		blitSprite(int x, int y, const std::string &spriteName, int width, int height)
    {
      struct winsize	win;
      int		my_x;
      int		my_y;

      ioctl(0, TIOCGWINSZ, &win);
      attron(COLOR_PAIR(this->_sprite[spriteName]));
      for (int i = 0; i < height; i += 5)
	{
	  for (int j = 0; j < width; j += 5)
	    {
	      my_x = (x + j) * win.ws_col / 1920;
	      my_y = (y + i) * win.ws_row / 1080;
	      mvprintw(my_y, my_x, ".");
	    }
	}
      attroff(COLOR_PAIR(this->_sprite[spriteName]));
    }

    virtual void		loadFont(const std::string&)
    {
    }

    virtual void		blitText(const std::string& text, int x, int y, int)
    {
      struct winsize	win;

      ioctl(0, TIOCGWINSZ, &win);
      int		my_x = x * win.ws_col / 1920;
      int		my_y = y * win.ws_row / 1080;
      mvprintw(my_y, my_x, text.c_str());
    }

    virtual void		refresh(void)
    {
      ::refresh();
      //clear();
    }

    virtual void		defCommand(std::vector<std::function<void (void *) >> tab, arcade::CmdMode mode)
    {
      if (mode == arcade::CmdMode::GAME)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('2', tab[0]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('3', tab[1]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('4', tab[2]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('5', tab[3]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('8', tab[4]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('9', tab[5]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(27, tab[6]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(KEY_LEFT, tab[7]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(KEY_RIGHT, tab[8]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(KEY_UP, tab[9]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(KEY_DOWN, tab[10]));
	}
      else if (mode == arcade::CmdMode::MENU)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('2', tab[0]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('3', tab[1]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('4', tab[2]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('5', tab[3]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>('a', tab[4]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(10, tab[5]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(127, tab[6]));
	  this->_cmd.insert(std::pair<int, std::function<void (void*)>>(27, tab[7]));
	}
    }

    virtual void		checkEvent(void)
    {
      int		c;

      c = getch();
      if (c >= 'a' && c <= 'z')
	this->_cmd['a'](&c);
      else if (this->_cmd.count(c))
	this->_cmd[c](NULL);
    }
  };
}


#endif /* !NCURSE_HPP */
