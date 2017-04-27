//
// main.cc for 201 in /home/erwan/Tek2/Math/201yams
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Wed Feb 15 11:20:47 2017 Erwan
// Last update Wed Feb 15 17:30:40 2017 Erwan
//

#include <iostream>
#include "yams.hh"

void	affHelp(char *binName)
{
  std::cout << "USAGE" << std::endl;
  std::cout << "           " << binName << " d1 d2 d3 d4 d5 c" << std::endl;
  std::cout << std::endl;
  std::cout << "DESCRIPTION" << std::endl;
  std::cout << "           d1\tvalue of the first die (0 is not throw)" << std::endl;
  std::cout << "           d2\tvalue of the second die (0 is not throw)" << std::endl;
  std::cout << "           d3\tvalue of the third die (0 is not throw)" << std::endl;
  std::cout << "           d4\tvalue of the fourth die (0 is not throw)" << std::endl;
  std::cout << "           d5\tvalue of the fifth die (0 is not throw)" << std::endl;
  std::cout << "           c\texpected combination" <<std::endl;
}

int	main(int ac, char **av)
{
  if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
    {
      affHelp(av[0]);
      return (0);
    }
  if (checkArg(ac, av) == 84)
    return (84);
  getProba(av);
  return (0);
}
