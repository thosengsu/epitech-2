/*
** checks.c for philosopher in /home/tomlenor/Documents/Tek2/PSU_2016_philo/src
**
** Made by tomlenor
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Wed Mar  8 10:30:43 2017 tomlenor
** Last update Thu Mar 16 13:31:42 2017 Erwan
*/

#include "philosopher.h"

int			check_if_eat_limit(int nb_philos)
{
  int			idx;

  idx = 0;
  while (idx < nb_philos)
    {
      if (g_philos[idx].cpt_eat == g_philos[idx].eat_occurence)
	return (ERROR_RET);
      idx++;
    }
  return (0);
}

int			check_if_num(char *str)
{
  int			cpt;

  cpt = 0;
  while (str[cpt] != '\0')
    {
      if (str[cpt] < '0' || str[cpt] > '9')
	return (ERROR_RET);
      cpt++;
    }
  return (0);
}

int			check_args(int ac, char **av)
{
  int			idx;

  idx = 1;
  if (ac != 5)
    return (ERROR_RET);
  while (idx < ac)
    {
      if ((idx % 2) == 0)
	{
	  if (check_if_num(av[idx]) == ERROR_RET)
	    return (ERROR_RET);
	  idx++;
	}
      else
	{
	  if (av[idx][0] != '-')
	    return (ERROR_RET);
	  else if (av[idx][1] == 'p' || av[idx][1] == 'e')
	    idx++;
	  else
	    return (ERROR_RET);
	}
    }
  return (0);
}
