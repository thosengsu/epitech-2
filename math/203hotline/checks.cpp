#include <string>
#include <iostream>

int			checkIfAlpha(std::string arg)
{
  for (size_t idx = 0; idx < arg.size(); idx++)
    {
      if (arg[idx] < '0' || arg[idx] > '9')
	{
	  std::cout << "arguments should be all alpha values." << std::endl;
	  return (84);
	}
    }
  return (0);
}

int			checksArgs(int ac, char **av)
{
  if (ac == 2)
    {
      std::string	arg1;
      arg1 = av[1];

      if (checkIfAlpha(arg1) == 84)
	return (84);
    }
  else if (ac == 3)
    {
      std::string	arg1;
      arg1 = av[1];
      std::string	arg2;
      arg2 = av[2];

      if (checkIfAlpha(arg1) == 84)
	return (84);
      else if (checkIfAlpha(arg2) == 84)
	return (84);
    }
  else
    {
      std::cout << "wrong number of arguments try the help: 203hotline -h" << std::endl;
      return (84);
    }
  return (0);
}
