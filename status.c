/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:49:17 by docho             #+#    #+#             */
/*   Updated: 2022/08/28 15:46:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	pick_up_fork(t_philo *philo)
{
	int			i;
	t_info		*info;
	long long	cur;

	i = philo->i;
	info = philo->info;
	if (pthread_mutex_lock(&(info->fork[philo->lrfork[i & 1]])) \
			|| !print_status(FORK, philo) || \
			pthread_mutex_lock(&(info->fork[philo->lrfork[(i & 1) ^ 1]])) \
			|| !print_status(FORK, philo))
		return (false);
	++(philo->cnt_eat);
	if (pthread_mutex_lock(&(philo->info->print)) \
			|| !timestamp(&cur))
		return (false);
	printf("%lldms %d is eating\n", cur - philo->info->begin, philo->i + 1);
	if (pthread_mutex_unlock(&(philo->info->print)))
		return (false);
	if (pthread_mutex_lock(&(info->dead[i])))
		return (false);
	info->lastmeal[i] = cur;
	if (pthread_mutex_unlock(&(info->dead[i])) || !nap(info->eat, cur))
		return (false);
	return (true);
}
bool	eating(t_philo *philo)
{
	if (philo->info->npe != 0 && philo->cnt_eat >= philo->info->npe)
	{
		if (pthread_mutex_lock(&(philo->info->is_full)))
			return (false);
		++(philo->info->full);
		if (pthread_mutex_unlock(&(philo->info->is_full)))
			return (false);
	}
	if (pthread_mutex_unlock(&(philo->info->fork[philo->lrfork[0]])) || \
			pthread_mutex_unlock(&(philo->info->fork[philo->lrfork[1]])))
		return (false);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	long long	cur;

	if (!timestamp(&cur) || !print_status(SLEEPING, philo) \
			|| !nap(philo->info->sleep, cur))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo)
{

	if (!print_status(THINKING, philo) || usleep(100) == -1)
		return (false);
	return (true);
}
