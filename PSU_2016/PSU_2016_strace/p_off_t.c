/*
** p_off_t.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 12 19:40:24 2017 MonsieurTom
** Last update Fri Apr 14 21:20:57 2017 MonsieurTom
*/

#include <stdio.h>
#include <unistd.h>
#include "strace.h"

int		p_off_t(pid_t child __attribute__((unused)),
			long reg_value)
{
  if (g_s == true)
    {
      if (reg_value)
	return (printf("0x%lx", reg_value));
      else
	return (printf("0"));
    }
  else
    return (printf("0x%x", (unsigned int)reg_value));
}
