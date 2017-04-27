/*
** open.c for strace in /home/tom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Thu Apr 13 01:31:11 2017 MonsieurTom
** Last update Sun Apr 16 14:43:11 2017 Alexis Lavenu
*/

#include <stdbool.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

static t_flag		g_open_flags[] =
  {
    {O_APPEND, "O_APPEND"},
    {O_ASYNC, "O_ASYNC"},
    {O_CLOEXEC, "O_CLOEXEC"},
    {O_CREAT, "O_CREAT"},
    {O_DIRECTORY, "O_DIRECTORY"},
    {O_EXCL, "O_EXCL"},
    {O_NOCTTY, "O_NOCTTY"},
    {O_NOFOLLOW, "O_NOFOLLOW"},
    {O_NONBLOCK, "O_NONBLOCK"},
    {O_SYNC, "O_SYNC"},
    {O_TRUNC, "O_TRUNC"},
    {0, NULL}
  };

int			print_open_flags(long flags)
{
  int			cpt;
  int			nb_spaces;

  nb_spaces = 0;
  cpt = 0;
  if (g_s == false)
    return (printf("0x%x", (unsigned int)flags));
  else if (flags & O_RDWR)
    nb_spaces += printf("O_RDWR");
  else if (flags & O_WRONLY)
    nb_spaces += printf("O_WRONLY");
  else
    nb_spaces += printf("O_RDONLY");
  while (g_open_flags[cpt].flag_name != NULL)
    {
      if (g_open_flags[cpt].flag & flags)
	nb_spaces += printf("|%s", g_open_flags[cpt].flag_name);
      cpt += 1;
    }
  return (nb_spaces);
}

void			print_open(pid_t child, struct user_regs_struct data,
				   long return_v)
{
  int			nb_spaces;

  nb_spaces = 0;
  nb_spaces += printf("open(");
  nb_spaces += p_char_p(child, find_reg(data, 0));
  nb_spaces += printf(", ");
  nb_spaces += print_open_flags(find_reg(data, 1));
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
