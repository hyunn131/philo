/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:11:09 by docho             #+#    #+#             */
/*   Updated: 2022/08/28 15:46:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	timestamp(long long *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (false);
	*time = (long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (true);
}

bool	nap(long long msec, long long start)
{
	long long	dt;
	long long	cur;

	dt = 50;
	if (!timestamp(&cur))
		return (false);
	while (cur - start < msec)
	{
		if (usleep(dt) == -1)
			return (false);
		if (!timestamp(&cur))
			return (false);
	}
	return (true);
}

bool	print_status(t_status status, t_philo *philo)
{
	long long cur;

	if (pthread_mutex_lock(&(philo->info->print)) \
			|| !timestamp(&cur))
		return (false);
	if (status == FORK)
		printf("%lldms %d has taken a fork\n", cur - philo->info->begin, philo->i + 1);
	else if (status == SLEEPING)
		printf("%lldms %d is sleeping\n", cur - philo->info->begin, philo->i + 1);
	else if (status == THINKING)
		printf("%lldms %d is thinking\n", cur - philo->info->begin, philo->i + 1);
	else if (status == DEAD)
	{
		printf("%lldms %d died\n", cur - philo->info->begin, philo->i + 1);
		return (true);
	}
	if (pthread_mutex_unlock(&(philo->info->print)))
		return (false);
	return (true);
}
