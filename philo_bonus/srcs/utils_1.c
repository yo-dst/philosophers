/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:04:00 by ydanset           #+#    #+#             */
/*   Updated: 2022/01/25 15:04:12 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(size * count);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count * size)
		res[i++] = '\0';
	return ((void *)res);
}

static char	*ft_strdup(char *s1)
{
	char	*res;
	int		i;

	res = ft_calloc(ft_strlen(s1) + 1, 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	return (res);
}

static int	get_len_res(int n)
{
	int	res;

	if (!n)
		return (1);
	res = 0;
	if (n < 0)
		res++;
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len_res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len_res = get_len_res(n);
	res = malloc(get_len_res(n) + 1);
	if (!res)
		return (NULL);
	if (!n)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	res[len_res] = '\0';
	while (n)
	{
		res[--len_res] = (n % 10) + 48;
		n /= 10;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}
