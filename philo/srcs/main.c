/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:10:30 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:11:19 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_philo *ph, t_mutex *mu)
{
	int	i;

	i = 0;
	while (i < ph->info->nb_ph)
	{
		pthread_mutex_destroy(&mu->forks[i]);
		pthread_mutex_destroy(&mu->eat_or_die[i]);
		i++;
	}
	pthread_mutex_destroy(&mu->log);
	pthread_mutex_destroy(&mu->nb_ph_fed);
	free(mu->forks);
	free(mu->eat_or_die);
	free(ph);
}

static int	on_error(char *msg, int code)
{
	printf("Error: %s\n", msg);
	return (code);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_mutex	mu;
	t_philo	*ph;

	if (!init_info(ac, av, &info))
		return (on_error("Invalid parameters", EXIT_FAILURE));
	if (!info.nb_ph)
		return (EXIT_SUCCESS);
	if (info.nb_meal_per_ph == 0)
	{
		printf("Everyone is happy and has le ventre rempli !\n");
		return (EXIT_SUCCESS);
	}
	if (!init_mutex(&info, &mu) || !init_philo(&ph, &info, &mu))
		return (on_error("Initialisation failure", EXIT_FAILURE));
	if (!create_threads(ph))
	{
		clean(ph, &mu);
		return (on_error("pthread_create() failure", EXIT_FAILURE));
	}
	join_threads(ph);
	clean(ph, &mu);
	return (EXIT_SUCCESS);
}
