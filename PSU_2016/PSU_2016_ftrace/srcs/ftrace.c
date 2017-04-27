/*
** ftrace.c for ftrace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_ftrace/srcs
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Wed Apr 19 12:19:54 2017 MonsieurTom
** Last update Thu Apr 27 11:18:59 2017 MonsieurTom
*/

#include <sys/ptrace.h>
#include <unistd.h>
#include "ftrace.h"

void		my_ftrace_main(pid_t child)
{

}

int		run_exec(char **av)
{
  char		*path;

  if ((path = get_path(av[1])) == NULL)
    return (return_E("Error: file doesn't exist or no path defined"));
  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
    return (return_E("Error: ptrace_traceme error"));
  if (execvp(path, av) == -1)
    return (return_E("Error: execvp error"));
  return (0);
}

int		my_ftrace(char **av)
{
  pid_t		child;

  if ((child = fork()) == -1)
    return (return_E("Error: fork seems to have crashed"));
  else if (!child)
    return (run_exec(av));
  else
    my_ftrace_main(child);
  return (0);
}
