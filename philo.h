/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:05:56 by docho             #+#    #+#             */
/*   Updated: 2022/08/28 15:46:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define DIVISION 100

typedef pthread_t		t_th;
typedef pthread_mutex_t	t_mu;

typedef enum e_status
{
	FORK,
	SLEEPING,
	THINKING,
	DEAD
}				t_status;

typedef struct s_info
{
	int			num;
	int			die;
	int			eat;
	int			sleep;
	int			npe;
	bool		error;
	long long	begin;
	t_mu		*fork;
	t_mu		*dead;
	t_mu		print;
	t_mu		is_full;
	int			full;
	long long	*lastmeal;
}				t_info;

typedef struct s_philo
{
	int			i;
	int			lrfork[2];
	t_th		th;
	int			cnt_eat;
	t_info		*info;
}				t_philo;

int		terminate(char *s);
void	*calloc_(size_t count, size_t size);
bool	atoi_(const char *str, int *num);
bool	pick_up_fork(t_philo *philo);
bool	eating(t_philo *philo);
bool	sleeping(t_philo *philo);
bool	thinking(t_philo *philo);
bool	timestamp(long long *time);
bool	nap(long long msec, long long start);
bool	print_status(t_status status, t_philo *philo);

#endif