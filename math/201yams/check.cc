//
// check.cc for 201yams in /home/tomlenor/Documents/Tek2/mathématiques/201yams
//
// Made by tomlenor
// Login   <tom.lenormand@epitech.eu>
//
// Started on  Wed Feb 15 11:46:14 2017 tomlenor
// Last update Thu Feb 23 16:52:34 2017 Erwan
//

#include <string>
#include <iostream>
#include <cstring>
#include "yams.hh"

int		checkDigit(std::string str)
{
  unsigned int	cpt = 0;

  while (cpt < str.size())
    {
      if (str[cpt] < '0' || str[cpt] > '6')
	{
	  std::cerr << "digit number must be between 1 and 6" << std::endl;
	  return (84);
	}
      cpt += 1;
    }
  return (0);
}

int		checkC(char *str)
{
  char		*tmpp = strdup(str);
  char		*tmp = strtok(tmpp, "_\0");
  std::string	sstr = tmp;
  int		convert;
  int		saveFull = 0;

  if (sstr == CombinationName[0])
    {
      if ((tmp = strtok(NULL, "\0")) == NULL)
	{
	  std::cerr << "You must enter a number after pair ex: pair_2" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if ((tmp = strtok(NULL, "\0")) != NULL)
	{
	  std::cerr << "You must only give one number as argument of pair" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "Number too high must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else if (sstr == CombinationName[1])
    {
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter a number after three ex: three_2" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (strtok(NULL, "_\0") != NULL)
	{
	  std::cerr << "too much number for a three combinaison, ex: three_2" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "Number too high must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else if (sstr == CombinationName[2])
    {
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter one number after four ex: four_4" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (strtok(NULL, "_\0") != NULL)
	{
	  std::cerr << "too much number for a four combinaison ex: four_4" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "Number too high must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else if (sstr == CombinationName[3])
    {
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter two numbers after full ex: full_4_2" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "your numbers must be between 0 and 6" << std::endl;
	      return (84);
	    }
	  saveFull = convert;
	}
      else
	return (84);
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter two numbers after full ex: full_4_2" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (strtok(NULL, "_\0") != NULL)
	{
	  std::cerr << "you must enter two numbers after full ex: full_4_2" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (saveFull == convert)
	    {
	      std::cerr << "can't do a full with the same numbers" << std::endl;
	      return (84);
	    }
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "your numbers must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else if (sstr == CombinationName[4])
    {
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter one numbers after straight ex: straight_5 or straight_6" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (strtok(NULL, "_\0") != NULL)
	{
	  std::cerr << "you must enter one numbers after straight ex: straight_5 or straight_6" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 5 || convert > 6)
	    {
	      std::cerr << "your numbers must be between 5 and 6 or 0" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else if (sstr == CombinationName[5])
    {
      if ((tmp = strtok(NULL, "_\0")) == NULL)
	{
	  std::cerr << "you must enter one number after yams ex: yams_4" << std::endl;
	  return (84);
	}
      sstr = tmp;
      if (strtok(NULL, "_\0") != NULL)
	{
	  std::cerr << "you must enter one number after yams ex: yams_4" << std::endl;
	  return (84);
	}
      if (checkDigit(sstr) == 0)
	{
	  convert = std::stoi(sstr);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "your numbers must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else
	return (84);
    }
  else
    {
      std::cerr << "combinaison name not know" << std::endl;
      return (84);
    }
  return (0);
}

int		checkArg(int ac, char **av)
{
  std::string	str;
  int		convert;

  if (ac != 7)
    {
      std::cerr << "you must enter 6 arguments ex: ./yams 2 3 4 5 6 full_2_4" << std::endl;
      return (84);
    }
  for (int i = 1; i < ac; i++)
    {
      str = av[i];
      if (i < 6)
	{
	  if (checkDigit(str) != 0)
	    return (84);
	  convert = std::stoi(str);
	  if (convert < 0 || convert > 6)
	    {
	      std::cerr << "numbers must be between 0 and 6" << std::endl;
	      return (84);
	    }
	}
      else if (i == 6)
	{
	  if (checkC(av[i]) == 84)
	    return (84);
	}
    }
  return (0);
}
