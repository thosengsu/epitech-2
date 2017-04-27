#ifndef SDL_HPP_
# define SDL_HPP_

# include <iostream>
# include <stdexcept>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <map>
# include <vector>
# include <string>
# include "ILib.hpp"

namespace arcade
{
  class SDL : public ILib
  {
  private :
    SDL_Window					*_win;
    TTF_Font					*_font;
    std::map<std::string, SDL_Texture *>	_sprite;
    std::map<SDL_Keycode, std::function<void (void *)>>	_cmd;
    SDL_Renderer				*_loadedSprite;

  public :
    SDL()
    {
      this->_win = NULL;
      this->_loadedSprite = NULL;
      this->_font = nullptr;
    }

    virtual ~SDL() {};

    //////////////
    // Start and Init the gfxLib.
    //////////////
    virtual void		init(const std::string &gameName = "Arcade")
    {
      if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
	  this->close();
	  throw (std::runtime_error(SDL_GetError()));
	}
      if (!(this->_win = (SDL_CreateWindow(gameName.c_str(), 0, 0, 1920, 1080, SDL_WINDOW_RESIZABLE))))
	{
	  this->close();
	  throw (std::runtime_error(SDL_GetError()));
	}
      if (!(this->_loadedSprite = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED)))
	{
	  this->close();
	  throw (std::runtime_error(SDL_GetError()));
	}
	if (TTF_Init() == -1)
	  {
	  this->close();
	  throw (std::runtime_error(SDL_GetError()));
	}
    }

    //////////////
    // properly close the gfxLib.
    //////////////
    virtual void		close(void)
    {
      for (auto i : this->_sprite)
	SDL_DestroyTexture(i.second);
      SDL_DestroyRenderer(this->_loadedSprite);
      if (this->_win)
	SDL_DestroyWindow(this->_win);
      SDL_Quit();
    }

    ///////////////
    // load a sprit on memory
    ///////////////
    virtual void		loadSprite(const std::string &name, const std::string &fileName)
    {
      SDL_Surface* pSprite = IMG_Load(fileName.c_str());

      if (pSprite != NULL)
	{
	  SDL_Texture	*pTexture = SDL_CreateTextureFromSurface(this->_loadedSprite,
								 pSprite);

	  if (pTexture != NULL)
	    {
	      this->_sprite[name] = pTexture;
	      SDL_FreeSurface(pSprite);
	    }
	  else
	    {
	      this->close();
	      throw (std::invalid_argument(SDL_GetError()));
	    }
	}
      else
	{
	  this->close();
	  throw (std::invalid_argument(SDL_GetError()));
	}
    }

    /////////////////
    // add a sprit previously added on the memory screen
    /////////////////
    virtual void		blitSprite(int x, int y, const std::string &spriteName, int width,
					   int height)
    {
      SDL_Rect	dest = {x , y, width, height};

      SDL_RenderCopy(this->_loadedSprite, this->_sprite[spriteName], NULL, &dest);
    }

    //////////////////
    // load a TTF library to be use later
    //////////////////
    virtual void		loadFont(const std::string& filename)
    {
      this->_font = TTF_OpenFont(filename.c_str(), 76);
      if (this->_font == nullptr)
	{
	  this->close();
	  throw(std::invalid_argument("TTF_OpenFont Bug"));
	}
    }

    //////////////////
    // add to the renderer the  previously loaded font
    //////////////////
    virtual void		blitText(const std::string& text, int x, int y, int size)
    {
      SDL_Color		textColor = {255, 255, 255, 255};
      SDL_Surface	*SText = TTF_RenderText_Solid(this->_font, text.c_str(), textColor);
      SDL_Texture	*TText = SDL_CreateTextureFromSurface(this->_loadedSprite, SText);
      SDL_Rect		dest = {x , y, static_cast<int>(text.size()) *
				(size - static_cast<int>(text.size())), size};

      SDL_FreeSurface(SText);
      SDL_RenderCopy(this->_loadedSprite, TText, NULL, &dest);
      SDL_DestroyTexture(TText);
    }

    //////////////////
    // display previously blihted sprites
    //////////////////
    virtual void		refresh(void)
    {
      SDL_RenderPresent(this->_loadedSprite);
      SDL_RenderClear(this->_loadedSprite);
    }

    //////////////////
    // check if a key is press
    //////////////////
    virtual void		checkEvent(void)
    {
      SDL_Event		event;

      SDL_Delay(10);
      if (SDL_PollEvent(&event) == 1)
	{
	  if (event.type == SDL_KEYDOWN &&
	      (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z))
	    {
	      char	c = static_cast<char>(event.key.keysym.sym);
	      this->_cmd[SDLK_a](&c);
	    }
	  else if (event.type == SDL_KEYDOWN && this->_cmd.count(event.key.keysym.sym))
	    this->_cmd[event.key.keysym.sym](NULL);
	}
    }
    //////////////////
    // define commands in relation with events
    //////////////////
    virtual void		defCommand(std::vector<std::function<void (void *)>> tab,
					   arcade::CmdMode mode)
    {
      if (mode == arcade::CmdMode::GAME)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(233, tab[0]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(34, tab[1]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(39, tab[2]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(40, tab[3]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(95, tab[4]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(231, tab[5]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_ESCAPE, tab[6]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_LEFT, tab[7]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_RIGHT, tab[8]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_UP, tab[9]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_DOWN, tab[10]));
	}
      else if (mode == arcade::CmdMode::MENU)
	{
	  if (!this->_cmd.empty())
	    this->_cmd.erase(this->_cmd.begin(), this->_cmd.end());
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(233, tab[0]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(34, tab[1]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(39, tab[2]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(40, tab[3]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_a, tab[4]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_RETURN, tab[5]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_BACKSPACE, tab[6]));
	  this->_cmd.insert(std::pair<SDL_Keycode, std::function<void (void *)>>(SDLK_ESCAPE, tab[7]));

	}
    }
  };
}

#endif // !SDL_HPP_
