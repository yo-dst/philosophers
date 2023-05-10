/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:16 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:09:09 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/stop");
	sem_unlink("/log");
	sem_unlink("/ph_fed");
}

static void	clean(pid_t *pids, t_sema *sem)
{
	free(pids);
	delete_sem(sem);
}

static void	*monitor_all_fed(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->info->nb_ph)
	{
		sem_wait(data->sem->ph_fed);
		i++;
		if (data->stop)
			return (NULL);
	}
	if (i == data->info->nb_ph)
		print_last_log(data->info, data->sem, 0, 0);
	sem_post(data->sem->stop);
	return (NULL);
}

static void	stop_monitor_all_fed(t_data *data)
{
	data->stop = 1;
	sem_post(data->sem->ph_fed);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_sema		sem;
	pid_t		*pids;
	t_data		data;

	if (!init_info(ac, av, &info))
		return (on_error("Invalid parameters", EXIT_FAILURE));
	pids = malloc(sizeof(pid_t) * info.nb_ph);
	if (!pids)
		return (on_error("malloc() failure", EXIT_FAILURE));
	unlink_sem();
	if (!init_sem(&sem, info.nb_ph))
		return (on_error("sem_open() failure", EXIT_FAILURE));
	init_data(&data, &info, &sem);
	if (pthread_create(&data.th, NULL, &monitor_all_fed, &data))
		return (on_error("pthread_create() failure", EXIT_FAILURE));
	if (!create_processes(pids, &info))
		return (on_error("fork() failure", EXIT_FAILURE));
	sem_wait(sem.stop);
	stop_monitor_all_fed(&data);
	kill_processes(pids, info.nb_ph);
	wait_processes(pids, info.nb_ph);
	pthread_join(data.th, NULL);
	clean(pids, &sem);
	return (EXIT_SUCCESS);
}
