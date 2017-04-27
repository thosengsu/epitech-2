//
// dlLoader.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/dlLoader
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Sat Mar 18 20:54:19 2017 Erwan
// Last update Fri Apr  7 19:51:58 2017 Erwan
//

#ifndef DLGAMELOADER_HPP
# define DLGAMELOADER_HPP

# include <string>
# include <vector>
# include "IGame.hpp"
# include "IDlGfxLoader.hpp"

/* ------------------- */
/* Loader for Game Lib */
/* ------------------- */

namespace arcade
{
  typedef arcade::GameExitState	(*launcher)(arcade::IDlGfxLoader *loader, const std::string &playerName);

  class dlGameLoader
  {
  public:
    /* ------------ */
    /* CTOR && DTOR */
    /* ------------ */
    dlGameLoader();
    ~dlGameLoader();

    /* ------ */
    /* GETTER */
    /* ------ */
    std::vector<std::string>		getGameLibNames(void) const;
    std::vector<std::string>::iterator	getCurrentGameLibIt(void) const;

    /* ----------------- */
    /* MEMBERS FUNCTIONS */
    /* ----------------- */
    arcade::launcher	getCurrentGameLauncher(void);
    arcade::launcher	getNextGameLauncher(void);
    arcade::launcher	getPreviousGameLauncher(void);

    void		setToNextGame(void);
    void		setToPreviousGame(void);

  private:
    /* ------------------ */
    /* PRIVATES FUNCTIONS */
    /* ------------------ */
    void		setHandler(void);
    arcade::launcher	getLauncher(void);

    void				*_handler;
    std::vector<std::string>			_gameLibNames;
    std::vector<std::string>::iterator	_currentGame;
  };
}

#endif /* !DLGAMELOADER_HPP */
