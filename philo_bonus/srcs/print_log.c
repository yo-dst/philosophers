/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:32 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:03:33 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(t_philo *ph, long time, int action)
{
	long	timestamps;
	int		n;

	n = ph->id + 1;
	sem_wait(ph->sem->log);
	timestamps = time_diff(ph->info->t_start, time);
	if (action == TAKE_FORK)
		printf("%ld %d has taken a fork\n", timestamps, n);
	else if (action == EAT)
		printf("%ld %d is eating\n", timestamps, n);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", timestamps, n);
	else if (action == THINK)
		printf("%ld %d is thinking\n", timestamps, n);
	sem_post(ph->sem->log);
}

void	print_last_log(t_info *info, t_sema *sem, int id, long time)
{
	sem_wait(sem->log);
	if (time)
		printf("%ld %d died\n", time_diff(info->t_start, time), id + 1);
	else
		printf("Everyone is happy and has le ventre rempli !\n");
}
