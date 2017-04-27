/*
** p_size_t.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 12 19:34:55 2017 MonsieurTom
** Last update Fri Apr 14 21:20:27 2017 MonsieurTom
*/

#include <stdio.h>
#include <unistd.h>
#include "strace.h"

int		p_size_t(pid_t child __attribute__((unused)),
			 long reg_value)
{
  int		nb_spaces;

  if (g_s == true)
    nb_spaces = printf("%lu", (size_t)reg_value);
  else
    nb_spaces = printf("0x%x", (unsigned int)reg_value);
  return (nb_spaces);
}
