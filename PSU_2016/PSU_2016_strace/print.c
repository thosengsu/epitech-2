/*
** print.c for strace in /home/monsieurtom/Documents/strace
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Wed Apr 12 12:33:17 2017 MonsieurTom
** Last update Sun Apr 16 14:44:46 2017 Alexis Lavenu
*/

#include <sys/user.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

const char	*g_special_tab[] =
  {
    "mmap",
    "mmap2",
    "access",
    "open",
    "read",
    "mprotect"
  };

t_fct_tab	g_fct_type[] =
  {
    {"int", p_int},
    {"size_t", p_size_t},
    {"off_t", p_off_t},
    {"const void *", p_void_p},
    {"void *", p_void_p},
    {"const char *", p_char_p},
    {"char *", p_char_p},
    {"unsigned char *", p_char_p},
    {"char **", p_char_pp},
    {NULL, (void *)0}
  };

void		print_syscalls_return(t_syscall *syscall, long return_v)
{
  if (g_s == true)
    {
      if (syscall->return_type == NULL)
	printf(" = ?\n");
      else
	{
	  if (return_v < 0)
	    printf(" = -1 ENOENT (%s)\n", strerror(-return_v));
	  else if (strchr(syscall->return_type, '*'))
	    printf(" = %#lx\n", return_v);
	  else
	    printf(" = %lx\n", return_v);
	}
    }
  else
    printf(" = 0x%x\n", (unsigned int)return_v);
}

int		print_syscalls_types(pid_t child, long reg_value, int cpt,
				     char *name)
{
  int		nb_spaces;

  nb_spaces = 0;
  if (cpt < 9 && strcmp(g_fct_type[cpt - 1].sys_type, "char **") == 0 &&
      strcmp(name, "execve"))
    nb_spaces += g_fct_type[cpt].fct(child, reg_value);
  else if (strcmp(name, "write") == 0 &&
	   strcmp(g_fct_type[cpt - 1].sys_type, "const void *") == 0)
    nb_spaces += g_fct_type[5].fct(child, reg_value);
  else if (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt - 1].sys_type, "char **") != 0)
    nb_spaces += g_fct_type[cpt - 1].fct(child, reg_value);
  else
    nb_spaces += printf("0x%lx", (size_t)reg_value);
  return (nb_spaces);
}

int		print_syscall_arg(pid_t child, t_syscall *syscall, int param,
				  long reg_value)
{
  int		cpt;

  cpt = 0;
  if (param == 0)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param1) != 0);
  else if (param == 1)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param2) != 0);
  else if (param == 2)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param3) != 0);
  else if (param == 3)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param4) != 0);
  else if (param == 4)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param5) != 0);
  else if (param == 5)
    while (g_fct_type[cpt].sys_type != NULL
	   && strcmp(g_fct_type[cpt++].sys_type, syscall->param6) != 0);
  return (print_syscalls_types(child, reg_value, cpt, syscall->name));
}

void		print_normal_syscall(pid_t child, struct user_regs_struct data,
				     t_syscall *syscall, long return_v)
{
  int		nb_spaces;
  unsigned int	idx;

  nb_spaces = 0;
  idx = 0;
  nb_spaces += printf("%s(", syscall->name);
  while (idx < syscall->nb_param)
    {
      if (idx >= 1)
	nb_spaces += printf(", ");
      nb_spaces += print_syscall_arg(child, syscall, idx, find_reg(data, idx));
      idx += 1;
    }
  nb_spaces += printf(")");
  while (nb_spaces < 39)
    {
      printf(" ");
      nb_spaces += 1;
    }
  print_syscalls_return(syscall, return_v);
}

void		print_syscall(pid_t child, struct user_regs_struct data,
			      t_syscall *syscall, long return_v)
{
  ssize_t	cpt;

  cpt = 0;
  while (cpt < 6)
    {
      if (strcmp(syscall->name, g_special_tab[cpt]) == 0)
	break;
      cpt++;
    }
  if (cpt == 6)
    print_normal_syscall(child, data, syscall, return_v);
  else if (cpt == 0)
    print_mmap(child, data, return_v);
  else if (cpt == 1)
    print_mmap2(child, data, return_v);
  else if (cpt == 2)
    print_access(child, data, return_v);
  else if (cpt == 3)
    print_open(child, data, return_v);
  else if (cpt == 4)
    print_read(child, data, return_v);
  else if (cpt == 5)
    print_mprotect(child, data, return_v);
}
