#include <iostream>
#include <exception>
#include "Menu.hpp"

#define ERROR	84
#define OK	0

void	aff_usage(char *bin)
{
  std::cout << bin << ", Usage: gfx_lib.so" << std::endl;
  std::cout << std::endl;
  std::cout << "Gfx lib can be found in \"lib\" directory." << std::endl;
  std::cout << "Games are in the \"games\" directory." << std::endl;
}

int	main(int ac, char **av)
{
  arcade::Menu	*menu;

  if (ac != 2)
    aff_usage(av[0]);
  else
    {
      try
	{
	  menu = new arcade::Menu(static_cast<std::string>(av[1]));
	  menu->loop();
	  delete menu;
	}
      catch (const std::exception &error)
	{
	  std::cerr << error.what() << std::endl;
	  return (ERROR);
	}
    }
  return (OK);
}
