/*
** actions.c for philosopher in /home/tomlenor/Documents/Tek2/PSU_2016_philo
**
** Made by tomlenor
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Wed Mar  8 12:16:12 2017 tomlenor
** Last update Sun Mar 19 17:33:41 2017 tomlenor
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "extern.h"
#include "philosopher.h"

#define SLEEP_UNIT 4500

void			do_think(t_philo *philo)
{
  int			chopstick_idx;

  if (g_chop_stick[philo->idx].phase == 1)
    chopstick_idx = (philo->idx + 1) % philo->nb_philos;
  else
    chopstick_idx = philo->idx;
  philo->phase = 2;
  g_chop_stick[chopstick_idx].phase = 1;
  lphilo_take_chopstick(&g_chop_stick[chopstick_idx].thread);
  lphilo_think();
  usleep(SLEEP_UNIT * 2);
  g_chop_stick[chopstick_idx].phase = 0;
  lphilo_release_chopstick(&g_chop_stick[chopstick_idx].thread);
}

void			do_rest(t_philo *philo)
{
  philo->phase = 3;
  lphilo_sleep();
}

void			do_eat(t_philo *philo)
{
  philo->phase = 1;
  g_chop_stick[philo->idx].phase = 1;
  lphilo_take_chopstick(&g_chop_stick[philo->idx].thread);
  g_chop_stick[(philo->idx + 1) % philo->nb_philos].phase = 1;
  lphilo_take_chopstick(&g_chop_stick[(philo->idx + 1)
				     % philo->nb_philos].thread);
  lphilo_eat();
  usleep(SLEEP_UNIT);
  philo->cpt_eat += 1;
  if (philo->cpt_eat == philo->eat_occurence)
    g_finish = 1;
  g_chop_stick[philo->idx].phase = 0;
  lphilo_release_chopstick(&g_chop_stick[philo->idx].thread);
  g_chop_stick[(philo->idx + 1) % philo->nb_philos].phase = 0;
  lphilo_release_chopstick(&g_chop_stick[(philo->idx + 1)
					% philo->nb_philos].thread);
}

void			*do_action(void *param)
{
  t_philo		*philo;

  philo = (t_philo *)param;
  while (g_finish == 0)
    {
      if ((g_chop_stick[philo->idx].phase == 0 ||
	  g_chop_stick[(philo->idx + 1) % philo->nb_philos].phase == 0)
	  && philo->phase == 3)
	do_think(philo);
      else if (g_chop_stick[philo->idx].phase == 0
	       && g_chop_stick[(philo->idx + 1) % philo->nb_philos].phase == 0
	       && philo->phase != 1)
	do_eat(philo);
      else if (philo->phase != 2 && philo->phase != 3)
	do_rest(philo);
    }
  pthread_exit(NULL);
  return (NULL);
}
