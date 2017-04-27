/*
** strace.h for strace in /home/monsieurtom/Documents/TEK2/PSU_2016/PSU_2016_strace/src
**
** Made by MonsieurTom
** Login   <tom.lenormand@epitech.eu>
**
** Started on  Mon Apr 10 17:57:21 2017 MonsieurTom
** Last update Sun Apr 16 14:51:07 2017 Alexis Lavenu
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <stdbool.h>
# include <unistd.h>
# include <sys/ptrace.h>
# include <sys/user.h>

typedef struct		s_syscall
{
  unsigned int		number;
  char			*name;
  unsigned int		nb_param;
  char			*return_type;
  char			*param1;
  char			*param2;
  char			*param3;
  char			*param4;
  char			*param5;
  char			*param6;
}			t_syscall;

typedef struct		s_flag
{
  int			flag;
  char			*flag_name;
}			t_flag;

typedef struct		s_fct_tab
{
  char			*sys_type;
  int			(*fct)(pid_t child, long reg_value);
}			t_fct_tab;

extern bool		g_s;

bool			my_signal(pid_t child);
void			check_signal(int status);
int			print_signal_exit(int wait_t);
int			strace_prog(char **av, char **env);
int			strace_pid(char *str_pid);
char			*get_path(char *av);
void			print_syscall(pid_t child, struct user_regs_struct data,
				      t_syscall *syscall, long return_v);
long			find_reg(struct user_regs_struct data, int num_param);
t_syscall		*strace_get_syscall(unsigned int number);
int			p_int(pid_t child, long reg_value);
int			p_off_t(pid_t child, long reg_value);
int			p_void_p(pid_t child, long reg_value);
int			p_char_p(pid_t child, long reg_value);
int			p_size_t(pid_t child, long reg_value);
int			p_char_pp(pid_t child, long reg_value);
void			print_read(pid_t child, struct user_regs_struct data,
				   long return_v);
void			print_mmap(pid_t child, struct user_regs_struct data,
				   long return_v);
void			print_mmap2(pid_t child, struct user_regs_struct data,
				    long return_v);
void			print_open(pid_t child, struct user_regs_struct data,
				   long return_v);
void			print_access(pid_t child, struct user_regs_struct data,
				     long return_v);
void			print_mprotect(pid_t child, struct user_regs_struct dat,
				       long return_v);

#endif /* !STRACE_H_ */
