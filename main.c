/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:14:23 by docho             #+#    #+#             */
/*   Updated: 2022/08/28 15:46:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *p_philo)
{
	t_philo		*philo;

	philo = p_philo;
	while (1)
	{
		if (!pick_up_fork(philo) || !eating(philo) || \
				!sleeping(philo) || !thinking(philo))
		{
			pthread_mutex_lock(&(philo->info->is_full));
				philo->info->full = 1 << 31;
			pthread_mutex_unlock(&(philo->info->is_full));
			return(NULL) ;
		}
	}
	return (NULL);
}

void	dead(t_info *info, t_philo *philo)
{
	long long	cur;
	int			i;

	while (1)
	{
		i = -1;
		while (++i < info->num)
		{
			if (!timestamp(&cur) || pthread_mutex_lock(&(info->dead[i])))
				return ;
			if (cur - info->lastmeal[i]  >= (long long)info->die)
			{
				if (!print_status(DEAD, philo))
					return ;
				info->error = false;
				return ;
			}
			if (pthread_mutex_unlock(&(info->dead[i])))
				return ;
		}
		if (pthread_mutex_lock(&(info->is_full)))
			return ;
		if (info->full < 0)
			return ;
		if (info->full >= info->num)
		{
			pthread_mutex_lock(&(philo->info->print));
			info->error = false;
			return ;
		}
		if (pthread_mutex_unlock(&(philo->info->is_full)))
			return ;
	}
	return ;
}

bool	philosophers(t_info *info)
{
	int		i;
	t_philo	*philo;

	info->error = true;
	philo = calloc_(info->num, sizeof(t_philo));
	info->lastmeal = calloc_(info->num, sizeof(long long));
	if (!philo || !timestamp(&(info->begin)))
		return (false);
	i = -1;
	while (++i < info->num)
	{
		philo[i].i = i;
		philo[i].lrfork[1] = i;
		philo[i].lrfork[0] = (i + 1) % info->num;
		philo[i].info = info;

		info->lastmeal[i] = info->begin;
		
		if (pthread_create(&(philo[i].th), NULL, life, (void *)&philo[i]) \
				|| pthread_detach(philo[i].th))
			return (false);
	}
	dead(info, philo);
	if (info->error)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	memset(&info, 0, sizeof(t_info));
	if (!(argc == 5 || argc == 6) || !atoi_(argv[1], &(info.num)) || \
			!atoi_(argv[2], &(info.die)) || !atoi_(argv[3], &(info.eat)) \
			|| !atoi_(argv[4], &(info.sleep)) || \
			(argc == 6 && !atoi_(argv[5], &(info.npe))))
		return (terminate("Error: Wrong args"));
	if (info.num == 0 || info.die == 0 || (argc == 6 && info.npe == 0))
		return (0);
	info.fork = (t_mu *)calloc_(info.num, sizeof(t_mu));
	info.dead = (t_mu *)calloc_(info.num, sizeof(t_mu));
	if (!info.fork || !info.dead)
		return (terminate("Error: malloc error"));
	i = -1;
	while (++i < info.num)
		if (pthread_mutex_init(&(info.fork[i]), NULL) || \
				pthread_mutex_init(&(info.dead[i]), NULL))
			return (terminate("Error: mutex init error"));
	if (pthread_mutex_init(&(info.is_full), NULL) || \
			pthread_mutex_init(&(info.print), NULL))
		return (terminate("Error: mutex init error"));
	if (!philosophers(&info))
		return (terminate("Error"));
}
