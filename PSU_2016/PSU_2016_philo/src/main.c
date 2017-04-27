/*
** main.c for philosopher in /home/tomlenor/Documents/Tek2/PSU_2016_philo/src
**
** Made by tomlenor
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Tue Mar  7 11:40:47 2017 tomlenor
** Last update Sun Mar 19 21:11:53 2017 Erwan
*/

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "extern.h"
#include "philosopher.h"

t_philo			*g_philos;
t_chop_stick		*g_chop_stick;
int			g_finish;

void			philo_prepare(int nb_philo)
{
  int			idx;

  idx = 0;
  while (idx < nb_philo)
    {
      pthread_join(g_philos[idx].thread, NULL);
      idx++;
    }
}

int			init_philos(int nb_philos, int nb_eat)
{
  int			idx;

  idx = 0;
  if ((g_chop_stick = malloc(sizeof(t_chop_stick) * nb_philos)) == NULL)
    return (ERROR_RET);
  if ((g_philos = malloc(sizeof(t_philo) * nb_philos)) == NULL)
    return (ERROR_RET);
  g_finish = 0;
  while (idx < nb_philos)
    {
      g_chop_stick[idx].phase = 0;
      pthread_mutex_init(&(g_chop_stick[idx].thread), NULL);
      g_philos[idx].phase = 3;
      g_philos[idx].eat_occurence = nb_eat;
      g_philos[idx].cpt_eat = 0;
      g_philos[idx].nb_philos = nb_philos;
      g_philos[idx].idx = idx;
      pthread_create(&g_philos[idx].thread, NULL, do_action, &(g_philos[idx]));
      idx++;
    }
  philo_prepare(nb_philos);
  return (0);
}

int			main(int ac, char **av)
{
  int			nb_philo;
  int			nb_eat;

  RCFStartup(ac, av);
  if (check_args(ac, av) == ERROR_RET ||
      ((nb_philo = atoi((av[1][1] == 'p') ? av[2] : av[4])) <= 1))
    {
      RCFCleanup();
      return (ERROR_RET);
    }
  nb_eat = atoi((av[1][1] == 'e') ? av[2] : av[4]);
  if (nb_philo == 0 || nb_eat == 0 ||
      init_philos(nb_philo, nb_eat) == ERROR_RET)
    {
      RCFCleanup();
      return (ERROR_RET);
    }
  RCFCleanup();
  return (0);
}
