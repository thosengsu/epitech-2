/*
** access.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Thu Apr 13 01:13:05 2017 MonsieurTom
** Last update Fri Apr 14 21:43:48 2017 MonsieurTom
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

int		print_access_flags(long flags)
{
  int		nb_spaces;
  bool		first;

  first = true;
  nb_spaces = 0;
  if (g_s == true)
    return (printf("0x%x", (unsigned int)flags));
  if (flags == F_OK)
    nb_spaces += printf("F_OK");
  else
    {
      if (flags & R_OK)
	{
	  nb_spaces += printf((first == true) ? ("R_OK") : ("|R_OK"));
	  first = false;
	}
      if (flags & W_OK)
	{
	  nb_spaces += printf((first == true) ? ("W_OK") : ("|W_OK"));
	  first = false;
	}
      if (flags & X_OK)
	nb_spaces += printf((first == true) ? ("X_OK") : ("|X_OK"));
    }
  return (nb_spaces);
}

void		print_access(pid_t child, struct user_regs_struct data,
			     long return_v)
{
  int		nb_spaces;

  nb_spaces = 0;
  nb_spaces += printf("access(");
  nb_spaces += p_char_p(child, find_reg(data, 0));
  nb_spaces += printf(", ");
  nb_spaces += print_access_flags(find_reg(data, 1));
  nb_spaces += printf(")");
  while (nb_spaces < 39)
    {
      printf(" ");
      nb_spaces += 1;
    }
  printf(" = ");
  if (g_s == true)
    {
      if (return_v < 0)
	printf("-1 ENOENT (%s)", strerror(-return_v));
      else
	p_int(child, return_v);
    }
  else
    printf("0x%x", (unsigned int)return_v);
  printf("\n");
}
