//
// proba.cc for 201 in /home/erwan/Tek2/Math/201yams
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Wed Feb 15 11:39:52 2017 Erwan
// Last update Thu Feb 23 16:46:46 2017 Erwan
//

#include <string>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "yams.hh"

int	facto(int n)
 {
   unsigned int	retval = 1;

   for (int i = n; i > 1; --i)
     retval *= i;
   return retval;
 }

void	affProba(std::string combination, int value1, int value2, double percent)
{
  if (combination == CombinationName[FULL])
    std::cout << std::setprecision(2) << std::fixed
	      << "chances to get a " << value1 << " " << combination << " of " << value2 << ": "
	      << percent << "%" << std::endl;
  else if (combination == CombinationName[FOUR])
    std::cout << std::setprecision(2) << std::fixed
	      << "chances to get a " << value1 << " four-of-a-kind: " << percent << "%"
	      << std::endl;
  else if (combination == CombinationName[THREE])
    std::cout << std::setprecision(2) << std::fixed
	      << "chances to get a " << value1 << " three-of-a-kind: " << percent << "%"
	      << std::endl;
  else
    std::cout << std::setprecision(2) << std::fixed
	      << "chances to get a " << value1 << " " << combination << ": " << percent << "%"
	      << std::endl;
}

double		probaStraight(int nbNeedDie)
{
  double	proba;

  proba = 1;
  while (nbNeedDie > 0)
    {
      proba = proba * ((double)nbNeedDie / 6);
      --nbNeedDie;
    }
  return (proba);
}

int		getComb(int nbDieToRoll, int i)
{
  return (facto(nbDieToRoll) / (facto(i) * facto(nbDieToRoll - i)));
}

double		someProba(int nbDieToRoll, int i)
{
  int		nbComb;
  double	tmpProba;

  nbComb = getComb(nbDieToRoll, i);
  tmpProba = pow((double)1 / (double)6, i);
  tmpProba = ((double)((tmpProba * ((double)(nbComb)))));
  tmpProba = ((double)(tmpProba * (pow(((double)(5)) / ((double)(6)), nbDieToRoll - i))));
  return (tmpProba);
}

double		probaClassic(int nbDieToRoll, int nbNeedDie)
{
  double	proba = 0;
  int		i = nbNeedDie;

  while (i <= nbDieToRoll)
    {
      proba += someProba(nbDieToRoll, i);
      ++i;
    }
  return (proba);
}

double		probaFull(int nbDieToRoll, int *wantedDie, int value1, int value2, int wantedDieSize)
{
  double	proba;
  int		nbWantedV1 = 0;
  int		nbWantedV2 = 0;
  int		i = 0;

  while (i < wantedDieSize)
    {
      if (wantedDie[i] == value1)
	++nbWantedV1;
      else if (wantedDie[i] == value2)
	++nbWantedV2;
      ++i;
    }
  if (nbWantedV1 >= nbWantedV2)
    {
      proba = ((double)(getComb(nbDieToRoll, nbWantedV1)));
      proba = ((double)(proba / pow((double)6, (double)nbDieToRoll)));
    }
  else
    {
      proba = ((double)(getComb(nbDieToRoll, nbWantedV2)));
      proba = ((double)(proba / pow((double)6, (double)nbDieToRoll)));
    }
  return (proba);
}

void	getProba(char **av)
{
  int			die[5];
  std::string		combination;
  int			*wantedDie;
  int			i = 0;
  int			j;
  int			nbDieToRoll = 0;
  int			value1 = 0;
  int			value2 = 0;
  int			size;
  double		proba;

  die[0] = atoi(av[1]);
  die[1] = atoi(av[2]);
  die[2] = atoi(av[3]);
  die[3] = atoi(av[4]);
  die[4] = atoi(av[5]);

  combination = strtok(av[6], "_");;
  size = getCombinationSize(combination);

  if (combination == CombinationName[FULL])
    {
      value1 = atoi(strtok(NULL, "_"));
      value2 = atoi(strtok(NULL, "\0"));
    }
  else
    value1 = atoi(strtok(NULL, "\0"));
  wantedDie = getWantedDie(combination, value1, value2);

  /* Count number of die to re roll */
  while (i < 5)
    {
      if (die[i] != 0)
	{
	  j = 0;
	  while (j < size)
	    {
	      if (die[i] == wantedDie[j])
		{
		  wantedDie[j] = 0;
		  break;
		}
	      ++j;
	    }
	  if (j == size)
	    ++nbDieToRoll;
	}
      else
	++nbDieToRoll;
      ++i;
    }

  /* Check if all die are good */
  i = 0;
  j = 0;
  while (i < size)
    {
      if (wantedDie[i] != 0)
	++j;
      ++i;
    }

  if (j == 0)
    proba = 1;
  else if (combination == CombinationName[FULL])
    proba = probaFull(nbDieToRoll, wantedDie, value1, value2, size);
  else if (combination == CombinationName[STRAIGHT])
    proba = probaStraight(j);
  else
    proba = probaClassic(nbDieToRoll, j);

  affProba(combination, value1, value2, proba * 100);
}
