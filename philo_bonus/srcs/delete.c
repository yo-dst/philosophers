/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:02:58 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:02:59 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delete_sem_eat_or_die(sem_t *eat_or_die, int id)
{
	char	*str_id;
	char	*sem_name;

	sem_close(eat_or_die);
	str_id = ft_itoa(id);
	if (str_id)
	{
		sem_name = ft_strjoin("/eat_or_die", str_id);
		sem_unlink(sem_name);
		free(sem_name);
	}
	free(str_id);
}

void	delete_sem(t_sema *sem)
{
	sem_close(sem->forks);
	sem_close(sem->stop);
	sem_close(sem->log);
	sem_close(sem->ph_fed);
	sem_unlink("/forks");
	sem_unlink("/stop");
	sem_unlink("/log");
	sem_unlink("/ph_fed");
}

void	delete_philo(t_philo *ph)
{
	sem_close(ph->sem->forks);
	sem_close(ph->sem->stop);
	sem_close(ph->sem->log);
	sem_close(ph->sem->ph_fed);
	delete_sem_eat_or_die(ph->sem->eat_or_die, ph->id);
	free(ph->sem);
}
