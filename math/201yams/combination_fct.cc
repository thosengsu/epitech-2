//
// combination_fct.cc for 201 in /home/erwan/Tek2/Math/201yams
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Sat Feb 18 01:17:41 2017 Erwan
// Last update Thu Feb 23 14:14:43 2017 Erwan
//

#include <string>
#include <cstring>
#include "yams.hh"

int	getCombinationSize(std::string combination)
{
  if (combination == CombinationName[PAIR])
    return (S_PAIR);
  else if (combination == CombinationName[THREE])
    return (S_THREE);
  else if (combination == CombinationName[FOUR])
    return (S_FOUR);
  else if (combination == CombinationName[FULL])
    return (S_FULL);
  else if (combination == CombinationName[STRAIGHT])
    return (S_STRAIGHT);
  else if (combination == CombinationName[YAMS])
    return (S_YAMS);
  return (0);
}

int	*getWantedDie(std::string combination, int value1, int value2)
{
  int	*wantedDie;

  if (combination == CombinationName[PAIR])
    {
      wantedDie = new int[S_PAIR];
      wantedDie[0] = value1;
      wantedDie[1] = value1;
    }
  else if (combination == CombinationName[THREE])
    {
      wantedDie = new int[S_THREE];
      wantedDie[0] = value1;
      wantedDie[1] = value1;
      wantedDie[2] = value1;
    }
  else if (combination == CombinationName[FOUR])
    {
      wantedDie = new int[S_FOUR];
      wantedDie[0] = value1;
      wantedDie[1] = value1;
      wantedDie[2] = value1;
      wantedDie[3] = value1;
    }
  else if (combination == CombinationName[FULL])
    {
      wantedDie = new int[S_FULL];
      wantedDie[0] = value1;
      wantedDie[1] = value1;
      wantedDie[2] = value1;
      wantedDie[3] = value2;
      wantedDie[4] = value2;
    }
  else if (combination == CombinationName[STRAIGHT])
    {
      wantedDie = new int[S_STRAIGHT];
      wantedDie[0] = value1 - 4;
      wantedDie[1] = value1 - 3;
      wantedDie[2] = value1 - 2;
      wantedDie[3] = value1 - 1;
      wantedDie[4] = value1;
    }
  else if (combination == CombinationName[YAMS])
    {
      wantedDie = new int[S_YAMS];
      wantedDie[0] = value1;
      wantedDie[1] = value1;
      wantedDie[2] = value1;
      wantedDie[3] = value1;
      wantedDie[4] = value1;
    }
  return (wantedDie);
}
