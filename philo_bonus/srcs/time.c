/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:48 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:03:49 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	long			ms;
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec * 1e-3;
	return (ms);
}

long	time_diff(long start, long end)
{
	return (end - start);
}
