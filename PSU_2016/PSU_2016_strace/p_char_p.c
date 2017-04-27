/*
** p_char_p.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 12 19:48:38 2017 MonsieurTom
** Last update Fri Apr 14 21:19:59 2017 MonsieurTom
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include "strace.h"

int		p_char_p(pid_t child, long reg_value)
{
  int		nb_spaces;
  char		cchar;
  int		cpt;

  cpt = 0;
  nb_spaces = 0;
  if (g_s == false)
    return (printf("0x%x", (unsigned int)reg_value));
  nb_spaces += printf("\"");
  while ((cchar = ptrace(PTRACE_PEEKTEXT, child, reg_value + cpt, NULL))
	 && cpt < 60)
    {
      if (cchar == '\n')
	nb_spaces += printf("\\n");
      else
	nb_spaces += printf("%c", cchar);
      cpt += 1;
    }
  nb_spaces += printf("\"");
  if (cpt >= 60)
    nb_spaces += printf("...");
  return (nb_spaces);
}
