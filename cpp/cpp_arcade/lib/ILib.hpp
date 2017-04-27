//
// ILib.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/gfx_lib
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Thu Mar 16 15:03:11 2017 Erwan
// Last update Thu Apr  6 23:25:45 2017 Erwan
//

#ifndef ILIB_HPP_
# define ILIB_HPP_

# include <functional>
# include <string>
# include <vector>

const ssize_t	SC_WIDTH = 1920;
const ssize_t	SC_HEIGHT = 1080;

namespace arcade
{
  //typedef void (*cmdFunction)(void);

  typedef enum class	e_cmdMode : int
    {
      GAME,
      MENU,
    }			CmdMode;

  class ILib
  {
  public:
    virtual ~ILib() {};

    /* Initialize graphical display */
    virtual void	init(const std::string &windowName = "Arcade") = 0;

    /* Close and delete all instance of the GFX Lib */
    virtual void	close(void) = 0;

    /* Load a sprite form file or from ASCII tab*/
    virtual void	loadSprite(const std::string &spriteName,
				   const std::string &fileName) = 0;

    /* Blih a sprite at position X,Y with width,height size */
    virtual void	blitSprite(int x, int y, const std::string &spriteName,
				   int width, int height) = 0;

    /* load a font in memory */
    virtual void	loadFont(const std::string& filename) = 0;

    /* blit the previously loaded font*/
    virtual void	blitText(const std::string& text, int x, int y, int size) = 0;

    /* Refresh the display */
    virtual void	refresh(void) = 0;

    /* Definie fonction par event */
    virtual void	defCommand(std::vector<std::function<void (void *)>> cmdFctTab,
				   arcade::CmdMode mode) = 0;

    /* Analyse les events */
    virtual void	checkEvent(void) = 0;
  };
}

#endif /* !ILIB_HPP_ */
