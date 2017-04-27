//
// main.cpp for 204 in /home/erwan/Tek2/Math/204ducks
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Mon Mar 27 16:17:00 2017 Erwan
// Last update Thu Apr  6 10:02:05 2017 Erwan
//

#include <cstdlib>
#include <iostream>

static const int ERROR	= 84;
static const int OK	= 0;

int	checkArg(int ac, char **av)
{
  if (ac != 2)
    return (ERROR);

  for (unsigned int i = 0; av[1][i] != 0; i++)
    {
      if ((av[1][i] < '0' || av[1][i] > '9') && av[1][i] != '.' && av[1][i] != '-')
	return (ERROR);
    }
  return (OK);
}

double		getPercent(double a, double t)
{
  double	out;
  out = a + t;
  return (out);
}

int	compute(double a)
{
  (void)a;
  return (OK);
}

int	main(int ac, char **av)
{
  double	a = 0;

  if (checkArg(ac, av) == ERROR)
    return (ERROR);

  a = atof(av[1]);

  if (compute(a) == ERROR)
    return (ERROR);
  return (OK);
}
