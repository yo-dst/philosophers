/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:10:25 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:10:26 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_params(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	if (!str_is_number(av[1]) || !str_is_number(av[2])
		|| !str_is_number(av[3]) || !str_is_number(av[4]))
		return (0);
	if (ac == 6 && !str_is_number(av[5]))
		return (0);
	return (1);
}

static int	check_info(int ac, t_info *info)
{
	if (info->nb_ph < 0 || info->t_death < 0
		|| info->t_eat < 0 || info->t_sleep < 0)
		return (0);
	if (ac == 6 && info->nb_meal_per_ph < 0)
		return (0);
	return (1);
}

int	init_info(int ac, char **av, t_info *info)
{
	if (!check_params(ac, av))
		return (0);
	info->nb_ph = ft_atoi(av[1]);
	info->t_death = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->nb_meal_per_ph = -1;
	if (ac == 6)
		info->nb_meal_per_ph = ft_atoi(av[5]);
	if (!check_info(ac, info))
		return (0);
	info->stop = 0;
	info->nb_ph_fed = 0;
	info->t_start = 0;
	return (1);
}

int	init_mutex(t_info *info, t_mutex *mu)
{
	int	i;

	if (pthread_mutex_init(&mu->log, NULL)
		|| pthread_mutex_init(&mu->nb_ph_fed, NULL))
		return (0);
	mu->forks = malloc(sizeof(pthread_mutex_t) * info->nb_ph);
	if (!mu->forks)
		return (0);
	mu->eat_or_die = malloc(sizeof(pthread_mutex_t) * info->nb_ph);
	if (!mu->eat_or_die)
		return (0);
	i = 0;
	while (i < info->nb_ph)
	{
		if (pthread_mutex_init(&mu->forks[i], NULL)
			|| pthread_mutex_init(&mu->eat_or_die[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_philo **ph, t_info *info, t_mutex *mu)
{
	int		i;

	*ph = malloc(sizeof(t_philo) * info->nb_ph);
	if (!*ph)
		return (0);
	i = 0;
	while (i < info->nb_ph)
	{
		(*ph)[i].id = i;
		(*ph)[i].left_fork = (i + 1) % info->nb_ph;
		(*ph)[i].right_fork = i;
		(*ph)[i].nb_meal = 0;
		(*ph)[i].mu = mu;
		(*ph)[i].info = info;
		i++;
	}
	return (1);
}
