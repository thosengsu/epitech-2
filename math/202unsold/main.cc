#include <string>
#include <iostream>
#include "includes/includes.hh"

int		main(int ac, char **av)
{
  if (ac == 2)
    {
      if (checkIfHelp(av[1]) == 84)
	return (84);
    }
  else if (ac == 3)
    {
      if (checkArgs(av[1], av[2]) == 84)
	return (84);
      if (jointLaw(atof(av[1]), atof(av[2])) == 84)
	return (84);
      return (0);
    }
  else
    {
      std::cerr << "Bad usage, try : ./202unsold -h" << std::endl;
      return (84);
    }
}
