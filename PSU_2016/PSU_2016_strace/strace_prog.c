/*
** strace_prog.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Mon Apr 10 10:53:08 2017 MonsieurTom
** Last update Wed Apr 19 12:17:31 2017 MonsieurTom
*/

#include <sys/ptrace.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "strace.h"
#include "syscalls.h"

t_syscall			*strace_get_syscall(unsigned int number)
{
  int				cpt;

  cpt = 0;
  while (cpt <= 313 && g_syscalls[cpt].number != number)
    cpt += 1;
  if (cpt <= 313)
    return (&g_syscalls[cpt]);
  return (NULL);
}

int				strace_prog_read_syscall(pid_t child)
{
  struct user_regs_struct	data;
  struct user_regs_struct	return_v;
  t_syscall			*syscall;
  long				instruction;
  int				wait_t;

  if (ptrace(PTRACE_GETREGS, child, NULL, &data) == -1)
    return (84);
  if (((instruction = ptrace(PTRACE_PEEKTEXT, child, data.rip, NULL)) & 0xFFFF)
      != 0x050F)
    return (1);
  if ((int)data.rax < 0 || (int)data.rax > 313 ||
      (syscall = strace_get_syscall((int)data.rax)) == NULL)
    return (1);
  ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
  waitpid(child, &wait_t, 0);
  ptrace(PTRACE_GETREGS, child, NULL, &return_v);
  print_syscall(child, data, syscall, return_v.rax);
  return (wait_t);
}

int				strace_prog_main(pid_t child)
{
  int				wait_t;

  waitpid(child, &wait_t, 0);
  while (my_signal(wait_t) == true)
    {
      if (wait_t == 0)
	break;
      if ((wait_t = strace_prog_read_syscall(child)) == 84)
	break;
      if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) == -1)
	break;
      waitpid(child, &wait_t, 0);
      check_signal(wait_t);
    }
  return (print_signal_exit(wait_t));
}

int		run_exec(char **av)
{
  char		*path;

  if ((path = get_path(av[1])) == NULL)
    {
      printf("Error : %s : file doen't exist or no path defined\n", av[1]);
      return (84);
    }
  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
    {
      printf("%s: ptrace error\n", av[0]);
      return (84);
    }
  if (execvp(path, av + 1) == -1)
    {
      printf("%s: execve error\n", av[0]);
      return (84);
    }
  return (0);
}

int		strace_prog(char **av, char **env)
{
  pid_t		child;
  (void)env;

  if ((child = fork()) == -1)
    {
      printf("Error: fork seems to crashed\n");
      return (84);
    }
  else if (!child)
    return (run_exec(av));
  else
    strace_prog_main(child);
  return (0);
}
