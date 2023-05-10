/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:43 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:08:49 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor(void *arg)
{
	t_philo	*ph;
	long	time;

	ph = (t_philo *)arg;
	while (ph->alive)
	{
		sem_wait(ph->sem->eat_or_die);
		time = get_time();
		if (time > ph->t_last_meal + ph->info->t_death)
		{
			print_last_log(ph->info, ph->sem, ph->id, time);
			ph->alive = 0;
			sem_post(ph->sem->stop);
		}
		sem_post(ph->sem->eat_or_die);
		usleep(1000);
	}
	return (NULL);
}

static int	task(t_info *info, int id)
{
	t_philo	ph;

	if (!init_philo(&ph, info, id))
		exit_error("philo initialization failure");
	if (pthread_create(&ph.th, NULL, &monitor, &ph))
		exit_error("pthread_create() failure");
	while (ph.alive)
		philo_life(&ph);
	pthread_join(ph.th, NULL);
	delete_philo(&ph);
	exit(0);
}

int	create_processes(pid_t *pids, t_info *info)
{
	int	n;
	int	i;

	n = info->nb_ph / 2;
	i = -1;
	info->t_start = get_time();
	while (++i < n)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (0);
		if (pids[i] == 0)
			task(info, i);
	}
	usleep(100);
	while (i < info->nb_ph)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (0);
		if (pids[i] == 0)
			task(info, i);
		i++;
	}
	return (1);
}

void	wait_processes(pid_t *pids, int nb_ph)
{
	int	i;

	i = 0;
	while (i < nb_ph)
		waitpid(pids[i++], NULL, 0);
}

void	kill_processes(pid_t *pids, int nb_ph)
{
	int	i;

	i = 0;
	while (i < nb_ph)
		kill(pids[i++], SIGTERM);
}
