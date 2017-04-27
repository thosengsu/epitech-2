/*
** print_exit.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Sat Apr 15 08:52:36 2017 MonsieurTom
** Last update Sun Apr 16 17:21:14 2017 MonsieurTom
*/

#include <sys/wait.h>
#include <stdio.h>
#include "signames.h"

void    check_signal(int status)
{
  if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGTRAP)
    printf("--- %s ---\n", g_signames[WSTOPSIG(status)]);
}

int	print_signal_exit(int wait_t)
{
  if (wait_t == -1)
    return (84);
  else if (WIFEXITED(wait_t))
    printf("+++ exited with %d +++\n", WEXITSTATUS(wait_t));
  else if (WIFSIGNALED(wait_t))
    printf("+++ exited with %s +++\n", g_signames[WTERMSIG(wait_t)]);
  else if (WIFSTOPPED(wait_t))
    printf("+++ exited with %s +++\n", g_signames[WSTOPSIG(wait_t)]);
  return (0);
}
