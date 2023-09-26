/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:49:42 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/26 15:44:06 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

void	philo_echo_die(size_t time, size_t id);

int		check_deadlock(t_sim *sim, size_t time);
void	terminate_philos(t_sim *sim);

void	observer_main(t_sim *sim)
{
	static size_t	last_time;
	size_t			time;

	while (1)
	{
		pthread_mutex_lock(&sim->mutex);
		time = get_ms_from(sim->start_time);
		if (last_time != time)
		{
			if (!sim->progress)
				break ;
			else if (check_deadlock(sim, time) < 0)
				break ;
		}
		pthread_mutex_unlock(&sim->mutex);
		last_time = time;
		usleep(500);
	}
	pthread_mutex_unlock(&sim->mutex);
	terminate_philos(sim);
}

int	check_deadlock(t_sim *sim, size_t time)
{
	size_t	id;

	id = 0;
	while (id < sim->arg.philo_num)
	{
		if (time >= sim->philos[id].deadline)
		{
			philo_echo_die(time, id + 1);
			sim->progress = 0;
			return (-1);
		}
		id++;
	}
	return (0);
}

void	terminate_philos(t_sim *sim)
{
	size_t	id;

	if (sim->arg.philo_num == 1)
		pthread_detach(sim->philos[0].tid);
	else
	{
		id = 0;
		while (id < sim->arg.philo_num)
		{
			pthread_join(sim->philos[id].tid, NULL);
			id++;
		}
	}
}
