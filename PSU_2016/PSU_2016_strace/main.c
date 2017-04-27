/*
** main.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Mon Apr 10 10:17:36 2017 MonsieurTom
** Last update Sun Apr 16 14:40:54 2017 Alexis Lavenu
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "strace.h"

bool		g_s = false;

void		usage(void)
{
  printf("Usage : strace [-s] [-p <pid>|<command>]\n");
}

int		check_if_good(int ac, char **av)
{
  int		idx;
  int		cpt;

  idx = 0;
  cpt = 0;
  if (ac < 3)
    return (84);
  while (idx != ac && strcmp("-p", av[idx]) != 0)
    idx++;
  if (idx == ac || (g_s == true && idx == 0))
    return (84);
  if (idx + 1 == ac || idx + 2 != ac)
    return (84);
  else
    {
      while (av[idx + 1][cpt] != '\0')
	{
	  if (av[idx + 1][cpt] < '0' || av[idx + 1][cpt] > '9')
	    return (84);
	  cpt++;
	}
      return (idx + 1);
    }
  return (0);
}

int		find_mode(int ac, char **av)
{
  int		c;
  int		pid;

  if (strcmp(av[1], "-s") == 0)
    g_s = true;
  while ((c = getopt(ac, av, "sp")) != -1)
    {
      if ((char)c == 'p')
	{
	  if ((pid = check_if_good(ac, av)) == 84)
	    {
	      usage();
	      return (84);
	    }
	  else
	    return (strace_pid(av[pid]));
	}
    }
  return (0);
}

int		main(int ac, char **av, char **env)
{
  int		mode;

  if (ac < 2)
    {
      usage();
      return (84);
    }
  else
    {
      if ((mode = find_mode(ac, av)) == 84)
	return (84);
      else if (mode == 0)
	{
	  if (g_s == true && ac < 3)
	    {
	      usage();
	      return (84);
	    }
	  else if (g_s == true)
	    strace_prog(av + 1, env);
	  else
	    strace_prog(av, env);
	}
    }
  return (0);
}
