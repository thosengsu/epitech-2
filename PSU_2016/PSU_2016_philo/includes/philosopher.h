/*
** philosopher.h for philosopher in /home/tomlenor/Documents/Tek2/
**
** Made by tomlenor
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Wed Mar  8 10:38:04 2017 tomlenor
** Last update Sun Mar 19 17:37:57 2017 tomlenor
*/

#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

# include <pthread.h>

# define ERROR_RET	84

typedef struct		s_philo
{
  int			phase;
  pthread_t		thread;
  int			idx;
  int			nb_philos;
  int			eat_occurence;
  int			cpt_eat;
}			t_philo;

typedef struct		s_chop_stick
{
  int			phase;
  pthread_mutex_t	thread;
}			t_chop_stick;

extern t_philo		*g_philos;
extern t_chop_stick	*g_chop_stick;
extern int		g_finish;

int			check_args(int ac, char **av);
int			check_if_eat_limit(int nb_philos);
void			*do_action(void *param);

#endif /* !PHILOSOPHER_H_ */
