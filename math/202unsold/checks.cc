#include <string>
#include <iostream>
#include "includes/includes.hh"

int		checkDigit(std::string str)
{
  unsigned int	cpt = 0;

  while (cpt < str.size())
    {
      if (str[cpt] < '0' || str[cpt] > '9')
	{
	  std::cerr << "Arguments must must be digits numbers superior or equal to 50" << std::endl;
	  return (84);
	}
      cpt += 1;
    }
  return (0);
}

int		checkArgs(char *a, char *b)
{
  std::string	arg1(a);
  std::string	arg2(b);
  int		nb;

  if (checkDigit(arg1) == 84)
    return (84);
  if (checkDigit(arg2) == 84)
    return (84);
  if ((nb = std::stoi(arg1)) < 50 || (nb = std::stoi(arg2) < 50))
    {
      std::cerr << "Arguments must must be digits numbers superior or equal to 50" << std::endl;
      return (84);
    }
  return (0);
}

int		checkIfHelp(char *str)
{
  std::string	ch(str);

  if (ch == "-h")
    my_help();
  else
    {
      std::cerr << "Bad usage, try : ./202unsold -h" << std::endl;
      return (84);
    }
  return (0);
}
