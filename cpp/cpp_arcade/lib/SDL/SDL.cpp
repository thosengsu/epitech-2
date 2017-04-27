#include "ILib.hpp"
#include "SDL.hpp"

extern "C" arcade::ILib		*create_GFX(void)
{
  return (new arcade::SDL);
}
