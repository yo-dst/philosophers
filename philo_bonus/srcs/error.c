/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:04 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:03:07 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	on_error(char *msg, int code)
{
	printf("Error: %s\n", msg);
	return (code);
}

void	exit_error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}
