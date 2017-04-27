/*
** main.c for 205 in /home/erwan/Tek2/Math/205IQ
**
** Made by Erwan
** Login   <erwan.guiomar@epitech.eu>
**
** Started on  Wed Apr 12 11:03:06 2017 Erwan
// Last update Thu Apr 13 14:06:18 2017 Erwan
*/

#include <iostream>
#include <regex>
#include "my.hpp"

static const int	OK	= 0;
static const int	ERROR	= 84;

int		checkArg(int ac, char **av)
{
  int		idx = 1;
  std::regex	reg;

  if (ac < 3 || ac > 5)
    return (ERROR);

  reg = static_cast<std::regex>("^[0-9]+$");
  while (av[idx] != NULL)
    {
      if (std::regex_match(static_cast<std::string>(av[idx]), reg) != 1)
	return (ERROR);
      ++idx;
    }
  return (OK);
}

int	main(int ac, char **av)
{
  IQ	*iq;
  if (checkArg(ac, av) == ERROR)
    return (ERROR);
  try
    {
      if (ac == 3)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]));
      else if (ac == 4)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]), atoi(av[3]));
      else if (ac == 5)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]), atoi(av[4]), atoi(av[3]));

      iq->compute();
    }
  catch (const std::exception &error)
    {
      std::cerr << error.what() << std::endl;
      return (84);
    }

  delete iq;
  return (OK);
}
