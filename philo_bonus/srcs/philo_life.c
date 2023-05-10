/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:25 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:03:26 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_philo *ph)
{
	sem_wait(ph->sem->forks);
	print_log(ph, get_time(), TAKE_FORK);
	sem_wait(ph->sem->forks);
	print_log(ph, get_time(), TAKE_FORK);
}

static void	put_forks_back(t_philo *ph)
{
	sem_post(ph->sem->forks);
	sem_post(ph->sem->forks);
}

static void	philo_eat(t_philo *ph)
{
	long	time;

	sem_wait(ph->sem->eat_or_die);
	time = get_time();
	ph->t_last_meal = time;
	sem_post(ph->sem->eat_or_die);
	print_log(ph, time, EAT);
	ph->nb_meal++;
	if (ph->nb_meal == ph->info->nb_meal_per_ph)
		sem_post(ph->sem->ph_fed);
	msleep(ph->info->t_eat);
}

static void	philo_sleep(t_philo *ph)
{
	print_log(ph, get_time(), SLEEP);
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
