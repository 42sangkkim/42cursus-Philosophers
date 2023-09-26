/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:16:46 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/31 15:50:46 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

void	philo_echo_take_fork(size_t time, size_t id);
void	philo_echo_eat(size_t time, size_t id);
void	philo_echo_sleep(size_t time, size_t id);
void	philo_echo_think(size_t time, size_t id);
void	philo_echo_die(size_t time, size_t id);

void	philo_wait(t_philo *philo, size_t until);

void	philo_wait_fork(t_philo *philo, pthread_mutex_t *fork);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	*philo_main(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->alive = 1;
	while (philo->alive)
	{
		if (philo->id % 2)
		{
			philo_wait_fork(philo, philo->left_fork);
			philo_wait_fork(philo, philo->right_fork);
		}
		else
		{
			philo_wait_fork(philo, philo->right_fork);
			philo_wait_fork(philo, philo->left_fork);
		}
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	philo_wait_fork(t_philo *philo, pthread_mutex_t *fork)
{
	size_t	time;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(philo->mutex);
	time = get_ms_from(philo->sim->start_time);
	if (!philo->sim->progress || !philo->alive)
		philo->alive = 0;
	else if (time >= philo->deadline)
	{
		philo_echo_die(time, philo->id);
		philo->sim->progress = 0;
		philo->alive = 0;
	}
	else
		philo_echo_take_fork(time, philo->id);
	pthread_mutex_unlock(philo->mutex);
}

void	philo_eat(t_philo *philo)
{
	size_t			time;

	pthread_mutex_lock(philo->mutex);
	time = get_ms_from(philo->sim->start_time);
	if (!philo->sim->progress || !philo->alive)
		philo->alive = 0;
	else if (time >= philo->deadline)
	{
		philo_echo_die(time, philo->id);
		philo->sim->progress = 0;
		philo->alive = 0;
	}
	else
	{
		philo_echo_eat(time, philo->id);
		philo->deadline = time + philo->arg.time_to_die;
		if (philo->arg.option && philo->arg.must_eat == ++philo->eat_cnt)
			philo->sim->progress--;
	}
	pthread_mutex_unlock(philo->mutex);
	philo_wait(philo, time + philo->arg.time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->mutex);
	time = get_ms_from(philo->sim->start_time);
	if (!philo->sim->progress || !philo->alive)
		philo->alive = 0;
	else if (time >= philo->deadline)
	{
		philo_echo_die(time, philo->id);
		philo->sim->progress = 0;
		philo->alive = 0;
	}
	else
		philo_echo_sleep(time, philo->id);
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo_wait(philo, time + philo->arg.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->mutex);
	time = get_ms_from(philo->sim->start_time);
	if (!philo->sim->progress || !philo->alive)
		philo->alive = 0;
	else if (time >= philo->deadline)
	{
		philo_echo_die(time, philo->id);
		philo->sim->progress = 0;
		philo->alive = 0;
	}
	else
		philo_echo_think(time, philo->id);
	pthread_mutex_unlock(philo->mutex);
	usleep(500);
}
