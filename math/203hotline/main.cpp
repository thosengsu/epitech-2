#include "include.hpp"

int		main(int ac, char **av)
{
  if (checksArgs(ac, av) == 84)
    return (84);
  else if (ac == 2)
    compute1(getArgs(av[1]));
  else if (ac == 3 && getArgs(av[1]) > getArgs(av[2]))
    compute2(getArgs(av[1]), getArgs(av[2]));
  else
    return (84);
  return (0);
}
