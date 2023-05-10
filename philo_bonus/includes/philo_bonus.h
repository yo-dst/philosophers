/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:02:25 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:02:27 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>

# define TAKE_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_sema
{
	sem_t		*forks;
	sem_t		*stop;
	sem_t		*eat_or_die;
	sem_t		*log;
	sem_t		*ph_fed;
}	t_sema;

typedef struct s_info
{
	int		nb_ph;
	long	t_death;
	long	t_sleep;
	long	t_eat;
	int		nb_meal_per_ph;
	long	t_start;
}	t_info;

typedef struct s_philo
{
	pthread_t	th;
	int			id;
	int			nb_meal;
	long		t_last_meal;
	t_info		*info;
	t_sema		*sem;
	int			alive;
}	t_philo;

typedef struct s_data
{
	pthread_t	th;
	int			stop;
	t_info		*info;
	t_sema		*sem;
}	t_data;

// msleep
void	msleep(long ms);

// time
long	get_time(void);
long	time_diff(long start, long end);

// print_log
void	print_log(t_philo *ph, long time, int action);
void	print_last_log(t_info *info, t_sema *sem, int id, long time);

// init
int		init_info(int ac, char **av, t_info *info);
void	init_data(t_data *data, t_info *info, t_sema *sem);
int		init_sem(t_sema *sem, int nb_ph);
int		init_sem_eat_or_die(sem_t *eat_or_die, int id);
int		init_philo(t_philo *ph, t_info *info, int id);

// utils
int		ft_atoi(const char *str);
int		str_is_number(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_strlen(char *str);

// delete
void	delete_sem(t_sema *sem);
void	delete_sem_eat_or_die(sem_t *eat_or_die, int id);
void	delete_philo(t_philo *ph);

// philo_life
void	philo_life(t_philo *ph);

// processes
void	kill_processes(pid_t *pids, int nb_ph);
void	wait_processes(pid_t *pids, int nb_ph);
int		create_processes(pid_t *pids, t_info *info);

// error
int		on_error(char *msg, int code);
void	exit_error(char *msg);

// check
int		check_params(int ac, char **av);
int		check_info(int ac, t_info *info);

#endif
