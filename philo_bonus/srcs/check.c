/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:02:49 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:02:53 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_params(int ac, char **av)
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

int	check_info(int ac, t_info *info)
{
	if (info->nb_ph < 0 || info->t_death < 0
		|| info->t_eat < 0 || info->t_sleep < 0)
		return (0);
	if (ac == 6 && info->nb_meal_per_ph < 0)
		return (0);
	if (info->nb_ph == 0)
		exit(EXIT_SUCCESS);
	if (info->nb_meal_per_ph == 0)
	{
		printf("Everyone is happy and has le ventre rempli !\n");
		exit(EXIT_SUCCESS);
	}
	return (1);
}
