#include <iostream>
#include "my.hpp"

int	checkArgs(char *a, char *b, char *c, char *d)
{
  for (int idx = 0; a[idx] != '\0'; idx++)
    {
      if (a[idx] < '0' || a[idx] > '9')
	return (84);
    }
  for (int idx = 0; b[idx] != '\0'; idx++)
    {
      if (b[idx] < '0' || b[idx] > '9')
	return (84);
    }
  for (int idx = 0; c[idx] != '\0'; idx++)
    {
      if (c[idx] < '0' || c[idx] > '9')
	return (84);
    }
  for (int idx = 0; d[idx] != '\0'; idx++)
    {
      if (d[idx] < '0' || d[idx] > '9')
	return (84);
    }
}

int	main(int ac, char **av)
{
  if (ac != 5)
    {
      std::cout << ac << std::endl;
      return (84);
    }
  else if (checkArgs(av[1], av[2], av[3], av[4]) != 84)
    {
      My	kek(av[1], av[2] , av[3], av[4]);

      if (kek.run() == 84)
	return (84);
    }
  else
    return (84);
  return (0);
}
