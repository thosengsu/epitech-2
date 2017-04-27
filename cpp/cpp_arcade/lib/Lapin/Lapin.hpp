//
// lapin.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/gfx_lib/Lapin
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Thu Mar 16 14:35:38 2017 Erwan
// Last update Sun Apr  9 13:44:46 2017 Erwan
//

#include <iostream>

#include <string>
#include <map>
#include <stdexcept>
#include <vector>
#include <lapin.h>
#include "ILib.hpp"

typedef std::map<t_bunny_keysym, std::function<void (void *)>> keyMap;

/* ------------- */
/* CMD FUNCTIONS */
/* ------------- */
static t_bunny_response	key(t_bunny_event_state state, t_bunny_keysym key, void *data)
{
  keyMap	*cpy = static_cast<keyMap *>(data);

  if (state == GO_DOWN)
    {
      if (cpy->count(BKS_A) && key >= BKS_A && key <= BKS_Z)
	{
	  char	c = static_cast<char>(key) - static_cast<char>(BKS_A) + 'A';
	  (*cpy)[BKS_A](&c);
	}
      else if (cpy->count(key))
	(*cpy)[key](NULL);
    }
  return (EXIT_ON_SUCCESS);
}

static t_bunny_response	loop(void *)
{
  return (EXIT_ON_SUCCESS);
}

namespace arcade
{
  class Lapin : public ILib
  {
  public:
    /* ------------ */
    /* CTOR && DTOR */
    /* ------------ */
    Lapin()
    {
      this->_win = NULL;
    }

    virtual ~Lapin() {};

    /* ----------------- */
    /* MEMBERS FUNCTIONS */
    /* ----------------- */


    // Init display of the lib
    virtual void	init(const std::string &Name = "Arcade")
    {
      std::string	window;

      window = Name + " with libLapin.";
      if ((this->_win = bunny_start(SC_WIDTH, SC_HEIGHT, false, window.c_str())) == NULL)
	throw (std::runtime_error("Bunny_star_style crashed"));

      bunny_set_mouse_visibility(this->_win, true);
      bunny_set_key_repeat(this->_win, true);
      bunny_set_loop_main_function(&loop);
      bunny_set_key_response(&key);
      this->refresh();
    }

    // Close all display of the lib
    virtual void	close(void)
    {
      bunny_stop(this->_win);
      for (auto i : this->_sprites)
	bunny_delete_clipable(i.second);
      bunny_delete_clipable(&(this->_font->clipable));
    }

    // Load a sprite in memory
    virtual void		loadSprite(const std::string &spriteName, const std::string &fileName)
    {
      t_bunny_picture	*image = NULL;

      image = bunny_load_picture(fileName.c_str());
      if (this->_sprites.count(spriteName))
	{
	  this->_sprites[spriteName] = image;
	}
      else
	this->_sprites.insert(std::pair<std::string, t_bunny_picture *>(spriteName, image));
    }

    // Aff a sprite at position(x,y) with size (widht,height)
    virtual void	blitSprite(int x, int y, const std::string &spriteName, int width, int height)
    {
      t_bunny_position		pos;
      t_bunny_accurate_position	acc;

      pos.x = x;
      pos.y = y;

      acc.x = static_cast<double>(static_cast<double>(width) /
				  static_cast<double>(this->_sprites[spriteName]->clip_width));
      acc.y = static_cast<double>(static_cast<double>(height) /
				  static_cast<double>(this->_sprites[spriteName]->clip_height));
      this->_sprites[spriteName]->scale = acc;
      bunny_blit(&(this->_win->buffer), this->_sprites[spriteName], &pos);
    }

    // Load a front in memory
    virtual void	loadFont(const std::string &fileName)
    {
      t_bunny_position	size;

      size.x = 40;
      size.y = 40;

      this->_font = bunny_load_font(500, 50, fileName.c_str(), &size);
      if (this->_font == NULL)
	throw (std::runtime_error("Bunny load font crashed.\n"));

      this->_font->color = WHITE;
      this->_font->halign = BAL_LEFT;
      this->_font->valign = BAL_TOP;
      this->_font->string_offset = 0;
      this->_font->outline = 1;

      size.x = 0;
      size.y = 0;
      this->_font->offset = size;
    }

    // Aff text with the loaded front
    virtual void	blitText(const std::string &text, int x, int y, int size)
    {
      t_bunny_position	pos;

      pos.x = x;
      pos.y = y;

      bunny_clear(&(this->_font->clipable.buffer), COLOR(0, 0, 0, 0));
      this->_font->string = text.c_str();
      this->_font->string_len = text.size();
      bunny_draw(&(this->_font->clipable));
      bunny_blit(&(this->_win->buffer), &(this->_font->clipable), &pos);
      (void)text;
      (void)x;
      (void)y;
      (void)size;
    }

    // Refresh display
    virtual void	refresh(void)
    {
      bunny_display(this->_win);
      bunny_clear(&(this->_win->buffer), BLACK);
    }

    virtual void	defCommand(std::vector<std::function<void (void *)>> cmdFctTab,
				   arcade::CmdMode mode)
    {
      if (mode == arcade::CmdMode::GAME)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());

	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_2, cmdFctTab[0]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_3, cmdFctTab[1]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_QUOTE, cmdFctTab[2]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_5, cmdFctTab[3]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_8, cmdFctTab[4]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_9, cmdFctTab[5]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_ESCAPE, cmdFctTab[6]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_LEFT, cmdFctTab[7]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_RIGHT, cmdFctTab[8]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_UP, cmdFctTab[9]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_DOWN, cmdFctTab[10]));
	}
      else if (mode == arcade::CmdMode::MENU)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_2, cmdFctTab[0]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_3, cmdFctTab[1]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_QUOTE, cmdFctTab[2]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_5, cmdFctTab[3]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_A, cmdFctTab[4]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_RETURN, cmdFctTab[5]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_BACKSPACE, cmdFctTab[6]));
	  this->_cmd.insert(std::pair<t_bunny_keysym, std::function<void (void *)>>(BKS_ESCAPE, cmdFctTab[7]));
	}
    }

    virtual void	checkEvent(void)
    {
      bunny_loop(this->_win, 60, &(this->_cmd));
    }

  private:
    keyMap					_cmd;
    std::map<std::string, t_bunny_picture *>	_sprites;
    t_bunny_window				*_win;
    t_bunny_font				*_font;
  };
}
