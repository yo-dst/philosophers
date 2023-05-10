/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:10:48 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:12:09 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	protected_stop(t_philo *ph, long time)
{
	pthread_mutex_lock(&ph->mu->log);
	if (!ph->info->stop)
	{
		if (time)
			printf("%ld %d died\n", \
				time_diff(ph->info->t_start, time), ph->id + 1);
		else
			printf("Everyone is happy and has le ventre rempli !\n");
		ph->info->stop = 1;
	}
	pthread_mutex_unlock(&ph->mu->log);
}

static void	*monitor(void *arg)
{
	t_philo	*ph;
	long	time;

	ph = (t_philo *)arg;
	while (!ph->info->stop)
	{
		pthread_mutex_lock(&ph->mu->eat_or_die[ph->id]);
		time = get_time();
		if (time > ph->t_last_meal + ph->info->t_death)
			protected_stop(ph, time);
		pthread_mutex_unlock(&ph->mu->eat_or_die[ph->id]);
		if (!ph->info->stop && ph->info->nb_ph_fed == ph->info->nb_ph)
			protected_stop(ph, 0);
		usleep(1000);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo		*ph;
	pthread_t	th;

	ph = (t_philo *)arg;
	ph->t_last_meal = ph->info->t_start;
	if (pthread_create(&th, NULL, &monitor, ph))
		return (NULL);
	if (ph->info->nb_ph == 1)
	{
		print_log(ph, get_time(), TAKE_FORK);
		while (!ph->info->stop)
			continue ;
	}
	else
		while (!ph->info->stop)
			philo_life(ph);
	pthread_join(th, NULL);
	return (NULL);
}

int	create_threads(t_philo *ph)
{
	int	i;

	ph->info->t_start = get_time();
	i = 0;
	while (i < ph->info->nb_ph)
	{
		if (pthread_create(&ph[i].th, NULL, &routine, &ph[i]))
			return (0);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < ph->info->nb_ph)
	{
		if (pthread_create(&ph[i].th, NULL, &routine, &ph[i]))
			return (0);
		i += 2;
	}	
	return (1);
}

void	join_threads(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->info->nb_ph)
		pthread_join(ph[i++].th, NULL);
}
