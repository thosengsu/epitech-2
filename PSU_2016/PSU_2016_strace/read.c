/*
** read.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Thu Apr 13 01:52:57 2017 MonsieurTom
** Last update Sun Apr 16 14:54:31 2017 Alexis Lavenu
*/

#include <sys/user.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "strace.h"

int		print_read_buf(pid_t child, long reg)
{
  char		c;
  int		nb_spaces;
  int		cpt;

  cpt = 0;
  if (g_s == false)
    return (printf("0x%x", (unsigned int)reg));
  nb_spaces = printf("\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, child, reg + cpt, NULL)) && cpt < 60)
    {
      if (c == '\n')
	nb_spaces += printf("\\n");
      else
	{
	  if (c < 20 || c > 126)
	    nb_spaces += printf("\\%d", (int)c);
	  else
	    nb_spaces += printf("%c", c);
	}
      cpt += 1;
    }
  nb_spaces += printf("\"");
  if (cpt >= 60)
    nb_spaces += printf("...");
  return (nb_spaces);
}

void		print_read(pid_t child, struct user_regs_struct data,
			   long return_v)
{
  int		nb_spaces;

  nb_spaces = 0;
  nb_spaces += printf("read(");
  nb_spaces += p_int(child, find_reg(data, 0));
  nb_spaces += printf(", ");
  nb_spaces += print_read_buf(child, find_reg(data, 1));
  nb_spaces += printf(", ");
  nb_spaces += p_size_t(child, find_reg(data, 2)) + printf(")");
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
	printf("%ld", (ssize_t)return_v);
    }
  else
    printf("0x%x", (unsigned int)return_v);
  printf("\n");
}
