/*
** p_void_p.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 12 19:44:22 2017 MonsieurTom
** Last update Fri Apr 14 21:21:15 2017 MonsieurTom
*/

#include <stdio.h>
#include <unistd.h>
#include "strace.h"

int		p_void_p(pid_t pid __attribute__((unused)),
			 long reg_value)
{
  int		nb_spaces;

  if (g_s == true)
    {
      if (reg_value)
	nb_spaces = printf("%p", (void *)reg_value);
      else
	nb_spaces = printf("NULL");
    }
  else
    nb_spaces = printf("0x%x", (unsigned int)reg_value);
  return (nb_spaces);
}
