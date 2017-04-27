/*
** misc.c for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Mon Apr 10 10:58:56 2017 MonsieurTom
** Last update Thu Apr 13 02:55:31 2017 MonsieurTom
*/

#include <sys/user.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

bool			my_signal(int wait_t)
{
  if (WIFEXITED(wait_t) || WIFSIGNALED(wait_t))
    return (false);
  return (true);
}

char			*get_path_env(char *av, char *path)
{
  char			*tmp;
  char			*my_path;

  while ((tmp = strtok(path, ":")) != NULL)
    {
      my_path = strdup(tmp);
      my_path = realloc(my_path, strlen(my_path) + strlen(av) + 3);
      my_path = strcat(my_path, "/");
      my_path = strcat(my_path, av);
      if (access(my_path, X_OK) == 0)
	return (my_path);
      free(my_path);
      path = NULL;
      tmp = NULL;
    }
  return (NULL);
}

char			*get_path(char *av)
{
  char			*path;

  path = getenv("PATH");
  if ((av[0] == '.' && av[1] == '/') && access(av, X_OK) == 0)
    return (av);
  else if ((av[0] == '.' && av[1] == '/') && access(av, X_OK) != 0)
    return (NULL);
  if (path == NULL)
    {
      if (access(av, X_OK) != 0)
	return (NULL);
      return (av);
    }
  return (get_path_env(av, path));
}

long		find_reg(struct user_regs_struct data, int num_param)
{
  if (num_param == 0)
    return (data.rdi);
  else if (num_param == 1)
    return (data.rsi);
  else if (num_param == 2)
    return (data.rdx);
  else if (num_param == 3)
    return (data.rcx);
  else if (num_param == 4)
    return (data.r8);
  else if (num_param == 5)
    return (data.r9);
  return (0);
}
