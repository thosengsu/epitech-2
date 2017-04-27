/*
** strace_pud.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Mon Apr 10 10:34:07 2017 MonsieurTom
** Last update Sun Apr 16 14:49:45 2017 Alexis Lavenu
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include "strace.h"

int		strace_pid_read_syscall(pid_t child)
{
  struct user_regs_struct	data;
  struct user_regs_struct	return_v;
  t_syscall			*syscall;
  long				instruction;
  int				wait_t;

  if (ptrace(PTRACE_GETREGS, child, NULL, &data) == -1)
    {
      printf("Error: PTRACE_GETREGS crashed\n");
      return (84);
    }
  if (((instruction = ptrace(PTRACE_PEEKTEXT, child, data.rip, NULL)) & 0xFFFF)
      != 0x050F)
    return (1);
  if ((int)data.rax < 0 || (int)data.rax > 321 ||
      (syscall = strace_get_syscall((int)data.rax)) == NULL)
    return (1);
  ptrace(PTRACE_SINGLESTEP, child, NULL, 0);
  waitpid(child, &wait_t, 0);
  ptrace(PTRACE_GETREGS, child, NULL, &return_v);
  print_syscall(child, data, syscall, return_v.rax);
  return (0);
}

int		strace_pid_main(pid_t child)
{
  int				wait_t;

  waitpid(child, &wait_t, 0);
  while (my_signal(wait_t) == true)
    {
      if (wait_t == 0)
	break;
      if (strace_pid_read_syscall(child) == 84)
	break;
      if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) == -1)
	break;
      waitpid(child, &wait_t, 0);
      check_signal(wait_t);
    }
  return (print_signal_exit(wait_t));
}

int		strace_pid(char *str_pid)
{
  pid_t		pid;

pid = atoi(str_pid);
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
printf("strace: attach: ptrace(PTRACE_SEIZE, %s): No such process\n", str_pid);
      return (84);
    }
  ptrace(PTRACE_CONT, pid, NULL, NULL);
  if (strace_pid_main(pid) == -1)
    return (84);
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return (0);
}
