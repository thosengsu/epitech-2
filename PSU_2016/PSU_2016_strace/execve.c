/*
** execve.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 12 23:15:28 2017 MonsieurTom
** Last update Thu Apr 13 02:54:08 2017 MonsieurTom
*/

#include <unistd.h>
#include <sys/ptrace.h>
#include <stdio.h>

int		second_dim(pid_t child, long first_dim)
{
  char		c;
  int		nb_spaces;
  int		j;

  j = -1;
  nb_spaces = 0;
  while ((c = ptrace(PTRACE_PEEKTEXT, child, first_dim + ++j, NULL)) && j < 60)
    {
      if (c == '\n')
	nb_spaces += printf("\\n");
      else
	nb_spaces += printf("%c", c);
    }
  printf("\"");
  if (j >= 60)
    nb_spaces += printf("...");
  return (nb_spaces);
}

int		print_execve_strtab(pid_t child, long reg_value)
{
  long		first_dim;
  int		nb_spaces;
  int		i;

  i = 0;
  nb_spaces = 0;
  while ((first_dim = ptrace(PTRACE_PEEKTEXT, child, reg_value + i, NULL)))
    {
      nb_spaces += printf("[");
      nb_spaces += second_dim(child, first_dim);
      i += sizeof(long);
      if (ptrace(PTRACE_PEEKTEXT, child, reg_value + i, NULL))
	nb_spaces +=  printf(", ");
    }
  nb_spaces += printf("]");
  return (nb_spaces);
}

int		len_args(pid_t child, long reg_value)
{
  int		cpt;

  cpt = 0;
  while (ptrace(PTRACE_PEEKTEXT, child, reg_value + cpt, NULL))
    cpt += sizeof(long);
  return (cpt / sizeof(long));
}

int		p_char_pp(pid_t child, long reg_value)
{
  int		nb_args;
  int		nb_spaces;

  if ((nb_args = len_args(child, reg_value)) > 3)
    {
      nb_spaces = printf("[/* %d vars */]", nb_args);
      return (nb_spaces);
    }
  nb_spaces = print_execve_strtab(child, reg_value);
  return (nb_spaces);
}
