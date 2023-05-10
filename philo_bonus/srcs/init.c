/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:11 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:03:12 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	info->t_start = 0;
	return (1);
}

void	init_data(t_data *data, t_info *info, t_sema *sem)
{
	data->info = info;
	data->sem = sem;
	data->stop = 0;
}

int	init_philo(t_philo *ph, t_info *info, int id)
{
	t_sema	*sem;

	sem = malloc(sizeof(t_sema) * 1);
	if (!sem)
		return (0);
	if (!init_sem(sem, info->nb_ph))
		return (0);
	if (!init_sem_eat_or_die(sem->eat_or_die, id))
		return (0);
	ph->id = id;
	ph->alive = 1;
	ph->info = info;
	ph->sem = sem;
	ph->t_last_meal = info->t_start;
	ph->nb_meal = 0;
	return (1);
}

int	init_sem(t_sema *sem, int nb_ph)
{
	sem->forks = sem_open("/forks", O_CREAT, 0761, nb_ph);
	if (sem->forks == SEM_FAILED)
		return (0);
	sem->stop = sem_open("/stop", O_CREAT, 0761, 0);
	if (sem->stop == SEM_FAILED)
		return (0);
	sem->log = sem_open("/log", O_CREAT, 0761, 1);
	if (sem->log == SEM_FAILED)
		return (0);
	sem->ph_fed = sem_open("/ph_fed", O_CREAT, 0761, 0);
	if (sem->ph_fed == SEM_FAILED)
		return (0);
	return (1);
}

int	init_sem_eat_or_die(sem_t *eat_or_die, int id)
{
	char	*str_id;
	char	*sem_name;

	str_id = ft_itoa(id);
	if (!str_id)
		return (0);
	sem_name = ft_strjoin("/eat_or_die", str_id);
	if (!sem_name)
		return (0);
	eat_or_die = sem_open(sem_name, O_CREAT, 0761, 1);
	free(sem_name);
	free(str_id);
	if (eat_or_die == SEM_FAILED)
		return (0);
	return (1);
}
