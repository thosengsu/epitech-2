/*
** extern.h for philo in /home/erwan/Tek2/PSU/PSU_2016_philo
**
** Made by Erwan
** Login   <erwan.guiomar@epitech.eu>
**
** Started on  Tue Mar  7 10:44:59 2017 Erwan
** Last update Sun Mar 19 21:05:38 2017 Erwan
*/

#ifndef EXTERN_H_
# define EXTERN_H_

# include <pthread.h>

int	RCFStartup(int ac, char **av);
void	RCFCleanup();
int	lphilo_eat();
int	lphilo_sleep();
int	lphilo_think();
int	lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
int	lphilo_release_chopstick(const pthread_mutex_t *mutex_id);

#endif /* !EXTERN_H_ */
