//
// dlLoader.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/dlLoader
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Sat Mar 18 20:54:19 2017 Erwan
// Last update Sun Apr  9 21:13:42 2017 Erwan
//

#ifndef DLGFXLOADER_HPP
# define DLGFXLOADER_HPP

# include <string>
# include <vector>
# include "../lib/ILib.hpp"
# include "IDlGfxLoader.hpp"

/* ------------------ */
/* Loader for Gfx Lib */
/* ------------------ */

namespace arcade
{
  typedef arcade::ILib	*create_gfx(void);

  class dlGfxLoader : public IDlGfxLoader
  {
  public:
    /* ------------ */
    /* CTOR && DTOR */
    /* ------------ */
    dlGfxLoader(const std::string &gfxLibName);
    virtual ~dlGfxLoader();

    /* ----------------- */
    /* MEMBERS FUNCTIONS */
    /* ----------------- */
    virtual arcade::ILib	*getCurrentGfxLib(void);
    virtual arcade::ILib	*getNextGfxLib(void);
    virtual arcade::ILib	*getPreviousGfxLib(void);
    virtual void		closeOldGfx(void);

    /*------- */
    /* GETTER */
    /*------- */
    std::vector<std::string>		getGfxLibNames(void) const;
    std::vector<std::string>::iterator	getCurrentGfxLibIt(void) const;

    /* ----------- */
    /* VAR FOR BEN */
    /* ----------- */
    arcade::ILib			*current;
  private:

    /* ------------------ */
    /* PRIVATES FUNCTIONS */
    /* ------------------ */
    arcade::ILib	*getILib(void);
    void		setHandler(void);

    void				*_handler;
    void				*_handlerTmp;
    std::vector<std::string>		_gfxLibNames;
    std::vector<std::string>::iterator	_currentGfx;
  };
}

#endif /* !DLGFXLOADER_HPP */
