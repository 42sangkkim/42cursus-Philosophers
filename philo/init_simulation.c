/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:34:58 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/29 13:52:21 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

void	*philo_main(void *arg);

int		parse_arguments(t_arg *arg, int argc, char **argv);
int		init_values(t_sim *sim);
void	init_philosopher(t_philo *philo, t_sim *sim, size_t id);
int		create_philosophers(t_sim *sim);

int	init_simulation(t_sim *sim, int argc, char **argv)
{
	memset(sim, 0, sizeof(t_sim));
	if (parse_arguments(&sim->arg, argc, argv) < 0)
	{
		print("\033[0;33mInvalid arguments\n\033[0;0m");
		return (-1);
	}
	if (init_values(sim) < 0)
		return (-1);
	if (create_philosophers(sim) < 0)
		return (-1);
	return (0);
}

int	parse_arguments(t_arg *arg, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (parse_uint((unsigned int *)&arg->philo_num, argv[1]) < 0 \
		|| arg->philo_num == 0)
		return (-1);
	if (parse_uint((unsigned int *)&arg->time_to_die, argv[2]) < 0)
		return (-1);
	if (parse_uint((unsigned int *)&arg->time_to_eat, argv[3]) < 0)
		return (-1);
	if (parse_uint((unsigned int *)&arg->time_to_sleep, argv[4]) < 0)
		return (-1);
	if (argc == 5)
	{
		arg->option = 0;
		arg->must_eat = 0;
	}
	else
	{
		arg->option = 1;
		if (parse_uint((unsigned int *)&arg->must_eat, argv[5]) < 0)
			return (-1);
	}
	return (0);
}

int	init_values(t_sim *sim)
{
	size_t	i;

	sim->forks = malloc(sim->arg.philo_num * sizeof(pthread_mutex_t));
	if (sim->forks == NULL)
		return (-1);
	sim->philos = malloc(sim->arg.philo_num * sizeof(t_philo));
	if (sim->philos == NULL)
		return (free(sim->forks), -1);
	if (pthread_mutex_init(&sim->mutex, NULL) != 0)
		return (free(sim->philos), free(sim->forks), -1);
	i = 0;
	while (i < sim->arg.philo_num)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&sim->forks[i]);
			pthread_mutex_destroy(&sim->mutex);
			return (free(sim->forks), free(sim->philos), -1);
		}
		init_philosopher(&sim->philos[i], sim, i + 1);
		i++;
	}
	return (0);
}

void	init_philosopher(t_philo *philo, t_sim *sim, size_t id)
{
	philo->id = id;
	philo->deadline = sim->arg.time_to_die;
	philo->eat_cnt = 0;
	philo->right_fork = &(sim->forks[id - 1]);
	philo->left_fork = &(sim->forks[id % sim->arg.philo_num]);
	philo->mutex = &sim->mutex;
	philo->arg = sim->arg;
	philo->sim = sim;
}

int	create_philosophers(t_sim *sim)
{
	size_t	i;

	pthread_mutex_lock(&sim->mutex);
	i = 0;
	while (i < sim->arg.philo_num)
	{
		if (pthread_create(&(sim->philos[i].tid), NULL, \
				philo_main, &(sim->philos[i])) != 0)
		{
			while (i--)
				pthread_detach(sim->philos[i].tid);
			while (i < sim->arg.philo_num)
				pthread_mutex_destroy(&sim->forks[i++]);
			pthread_mutex_destroy(&sim->mutex);
			free(sim->forks);
			free(sim->philos);
			return (-1);
		}
		i++;
	}
	return (0);
}
