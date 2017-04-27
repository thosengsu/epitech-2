/*
** main.c for 205 in /home/erwan/Tek2/Math/205IQ
**
** Made by Erwan
** Login   <erwan.guiomar@epitech.eu>
**
** Started on  Wed Apr 12 11:03:06 2017 Erwan
// Last update Tue Apr 18 16:41:02 2017 Erwan
*/

#include <iostream>
#include <regex>
#include "my.hpp"
#include "Lapin.hpp"

void		checkArg(int ac, char **av)
{
  int		idx = 1;
  std::regex	reg;

  if (ac < 3 || ac > 5)
    throw (std::invalid_argument("Bad number of arguments. Try -h."));

  reg = static_cast<std::regex>("^[0-9]+$");
  while (av[idx] != NULL)
    {
      if (std::regex_match(static_cast<std::string>(av[idx]), reg) != 1)
	throw (std::invalid_argument("Arguments must be numbers."));
      ++idx;
    }
}

int	main(int ac, char **av)
{
  IQ	*iq;
  Lapin	*lapin;

  try
    {
      checkArg(ac, av);
      if (ac == 3)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]));
      else if (ac == 4)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]), atoi(av[3]));
      else if (ac == 5)
	iq = new IQ(ac, atoi(av[1]), atoi(av[2]), atoi(av[4]), atoi(av[3]));

      iq->compute();

      if (ac == 3)
	{
	  lapin = new Lapin(iq);

	  lapin->startLoop();
	}
    }
  catch (const std::exception &error)
    {
      std::cerr << error.what() << std::endl;
      return (84);
    }

  delete iq;
  return (0);
}
