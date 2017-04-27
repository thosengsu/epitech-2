//
// IGame.hpp for arcade in /home/erwan/Tek2/C++/cpp_arcade
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Sat Mar 18 16:20:23 2017 Erwan
// Last update Thu Apr  6 10:03:46 2017 Erwan
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <chrono>
# include <string>
# include "ILib.hpp"
# include "arcade_protocoll.hpp"

///////////////////////////
// Var For Map/Tile Size //
///////////////////////////
static const ssize_t	MAP_WIDTH = 30;
static const ssize_t	MAP_HEIGHT = 20;
static const ssize_t	TILE_SIZE_WIDTH = SC_WIDTH / MAP_WIDTH;
static const ssize_t	TILE_SIZE_HEIGHT = SC_HEIGHT / (MAP_HEIGHT + 1);
static const ssize_t	PACWIDTH = 33;
static const ssize_t	PACHEIGHT = 23;
static const ssize_t	PACTILE_WIDTH = 40;
static const ssize_t	PACTILE_HEIGHT = 40;

namespace arcade
{
  enum class		GameExitState : int
    {
      EXIT		= 0,
      PREVIOUS		= 1,
      NEXT		= 2,
      MENU		= 3,
      NOTHING		= 4
    };

  enum class		Dir : uint16_t
    {
      LEFT	= 0,
      RIGHT	= 1,
      DOWN	= 2,
      UP        = 3,
      NOTHING	= 4
    };

  typedef struct	s_pacman
  {
    ssize_t		gfx_x;
    ssize_t		gfx_y;
    arcade::WhereAmI	*me;
  }			t_pacman;

  typedef struct	s_ghostStuct
  {
    ssize_t		x;
    ssize_t		y;
    ssize_t		gfx_x;
    ssize_t		gfx_y;
    ssize_t		speed;
    bool		alive;
    bool		waiting;
    bool		chased;
    int			ocur;
    int			maxOcur;
    int			ocurChase;
    std::chrono::high_resolution_clock::time_point	refDead;
    std::chrono::high_resolution_clock::time_point	refChase;
    std::chrono::high_resolution_clock::time_point	refWaiting;
    std::chrono::milliseconds				timeChased;
    std::chrono::milliseconds				timeDead;
    arcade::Dir		direction;
  }			t_ghostStruct;

  typedef struct	s_pacgum
  {
    bool		eaten;
    ssize_t		x;
    ssize_t		y;
  }			t_pacgum;

  class IGame
  {
  public :
    virtual ~IGame() {};

    // virtual void	start() = 0;
    // virtual void	launchGame(std::string libName, t_arcade *arcade) = 0;
  };
}

extern "C" void	play();

#endif // !IGAME_HPP_
