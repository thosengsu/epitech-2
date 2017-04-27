/*
** mprotect.c for strace in /home/tom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Thu Apr 13 02:11:19 2017 MonsieurTom
** Last update Sun Apr 16 14:43:20 2017 Alexis Lavenu
*/

#include <sys/user.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "strace.h"

int		print_mprotect_prot(long proto)
{
  int		nb_spaces;
  bool		first;

  nb_spaces = 0;
  first = true;
  if (proto)
    {
      if (proto & PROT_READ)
	{
	  nb_spaces += printf("PROT READ");
	  first = false;
	}
      if (proto & PROT_WRITE)
	{
	  nb_spaces += printf((first == true) ? ("PROTE_WRITE") :
			      ("|PROT_WRITE"));
	  first = false;
	}
      if (proto & PROT_EXEC)
	nb_spaces += printf((first == true) ? ("PROTE_EXEC") : ("|PROT_EXEC"));
    }
  else
    nb_spaces += printf("PROT_NONE");
  return (nb_spaces);
}

void		print_mprotect(pid_t child, struct user_regs_struct data,
			       long return_v)
{
  int		nb_spaces;

  nb_spaces = 0;
  nb_spaces += printf("mprotect(");
  nb_spaces += p_void_p(child, find_reg(data, 0));
  nb_spaces += printf(", ");
  nb_spaces += p_size_t(child, find_reg(data, 1));
  nb_spaces += printf(", ");
  nb_spaces += print_mprotect_prot(find_reg(data, 2));
  nb_spaces += printf(")");
  while (nb_spaces < 39)
    {
      printf(" ");
      nb_spaces += 1;
    }
  printf(" = ");
  if (return_v < 0)
    printf("-1 ENOENT (%s)", strerror(-return_v));
  else
    p_int(child, return_v);
  printf("\n");
}
