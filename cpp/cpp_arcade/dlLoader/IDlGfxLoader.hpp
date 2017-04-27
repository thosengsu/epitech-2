//
// IDlGfxLoader.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/dlLoader
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Tue Mar 21 14:50:15 2017 Erwan
// Last update Tue Apr  4 14:22:41 2017 Erwan
//

#ifndef IDLGFXLOADER_HPP
# define IDLGFXLOADER_HPP

# include "../lib/ILib.hpp"

namespace arcade
{
  class IDlGfxLoader
  {
  public:
    virtual ~IDlGfxLoader() {};

    virtual arcade::ILib		*getCurrentGfxLib(void) = 0;
    virtual arcade::ILib		*getPreviousGfxLib(void) = 0;
    virtual arcade::ILib		*getNextGfxLib(void) = 0;
    virtual void			closeOldGfx(void) = 0;
    virtual std::vector<std::string>	getGfxLibNames(void) const = 0;
  };
}

#endif /* !IDLGFXLOADER_HPP */
