/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:10:40 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:10:41 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *ph)
{
	if (ph->id % 2)
	{
		pthread_mutex_lock(&ph->mu->forks[ph->left_fork]);
		print_log(ph, get_time(), TAKE_FORK);
		pthread_mutex_lock(&ph->mu->forks[ph->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&ph->mu->forks[ph->right_fork]);
		print_log(ph, get_time(), TAKE_FORK);
		pthread_mutex_lock(&ph->mu->forks[ph->left_fork]);
	}
	print_log(ph, get_time(), TAKE_FORK);
}

static void	put_forks_back(t_philo *ph)
{
	pthread_mutex_unlock(&ph->mu->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->mu->forks[ph->right_fork]);
}

static void	philo_eat(t_philo *ph)
{
	long	time;

	pthread_mutex_lock(&ph->mu->eat_or_die[ph->id]);
	time = get_time();
	print_log(ph, time, EAT);
	ph->t_last_meal = time;
	pthread_mutex_unlock(&ph->mu->eat_or_die[ph->id]);
	ph->nb_meal++;
	if (ph->nb_meal == ph->info->nb_meal_per_ph)
	{
		pthread_mutex_lock(&ph->mu->nb_ph_fed);
		ph->info->nb_ph_fed++;
		pthread_mutex_unlock(&ph->mu->nb_ph_fed);
	}
	if (!ph->info->stop)
		msleep(ph->info->t_eat);
}

static void	philo_sleep(t_philo *ph)
{
	print_log(ph, get_time(), SLEEP);
	if (!ph->info->stop)
		msleep(ph->info->t_sleep);
}

void	philo_life(t_philo *ph)
{
	take_forks(ph);
	philo_eat(ph);
	put_forks_back(ph);
	philo_sleep(ph);
	print_log(ph, get_time(), THINK);
	if (ph->info->nb_ph % 2)
		usleep(100);
}
