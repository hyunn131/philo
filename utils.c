/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:46:13 by docho             #+#    #+#             */
/*   Updated: 2022/08/28 15:46:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	strlen_(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	terminate(char *s)
{
	write(2, s, strlen_(s));
	write(2, "\n", 1);
	return (1);
}

void	*calloc_(size_t count, size_t size)
{
	void	*m;

	m = malloc(size * count);
	if (m)
	{
		memset(m, 0, size * count);
	}
	return (m);
}

bool	atoi_(const char *str, int *num)
{
	size_t	i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (false);
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = 10 * result + (str[i] - '0');
		i++;
		if (!((1 << 31) < result && result < (~(1 << 31))))
			return (false);
	}
	if (str[i] != 0)
		return (false);
	*num = result;
	return (true);
}
