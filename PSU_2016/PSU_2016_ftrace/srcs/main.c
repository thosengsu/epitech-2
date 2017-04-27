/*
** main.c for ftrace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_ftrace/srcs
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Tue Apr 18 11:11:47 2017 MonsieurTom
** Last update Wed Apr 19 12:47:18 2017 MonsieurTom
*/

#include <stdio.h>
#include "ftrace.h"

int		usage(void)
{
  printf("Usage: ./ftrace <commande>\n");
  return (84);
}

int		main(int ac, char **av)
{
  if (ac < 2)
    return (usage());
  else
    return (my_ftrace(av + 1));
  return (0);
}
