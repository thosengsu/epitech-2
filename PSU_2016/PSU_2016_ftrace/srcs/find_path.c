/*
** find_path.c for ftrace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_ftrace/srcs
** 
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
** 
** Started on  Wed Apr 19 12:30:56 2017 MonsieurTom
** Last update Wed Apr 19 12:54:01 2017 MonsieurTom
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char		*get_path_env(char *av, char *path)
{
  char		*tmp;
  char		*my_path;

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

char		*get_path(char *av)
{
  char		*path;

  path = getenv("PATH");
  if ((av[0] == '.' && av[1] == '/') && access(av, X_OK) == 0)
    return (av);
  else if ((av[0] == '.' && av[1] == '/') && access(av, X_OK) != 0)
    return (NULL);
  else if (path == NULL)
    {
      if (access(av, X_OK) != 0)
	return (NULL);
      return (av);
    }
  return (get_path_env(av, path));
}
