#ifndef MENU_HPP_
# define MENU_HPP_

# include <string>
# include "ILib.hpp"
# include "IDlGfxLoader.hpp"
# include "dlGfxLoader.hpp"
# include "dlGameLoader.hpp"

namespace arcade
{
  class Menu
  {
  public:
    /* ------------ */
    /* CTOR && DTOR */
    /* ------------ */
    Menu(const std::string &gfxLibName);
    ~Menu();

    /* ----------------- */
    /* MEMBERS FUNCTIONS */
    /* ----------------- */
    void	loop(void);
    void	checkEvent(void);
    void	affMenu(void) const;
    void	defCmd(void);

    /* ----------------- */
    /* COMMAND FUNCTIONS */
    /* ----------------- */
    void	nextGfx(void *);
    void	previousGfx(void *);
    void	nextGame(void *);
    void	previousGame(void *);
    void	writeName(void *);
    void	launchGame(void *);
    void	delCaraInName(void *);
    void	quit(void *);

  private:
    arcade::dlGfxLoader		*_dlGfxLoader;
    arcade::dlGameLoader	_dlGameLoader;
    std::string			_playerName;
    arcade::ILib		*_gfx;
    arcade::ILib		*_gfxTmp;
    bool			_start;
    bool			_leave;
  };
}

#endif /* !MENU_HPP_ */
