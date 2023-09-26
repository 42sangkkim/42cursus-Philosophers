/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:00:23 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/27 14:04:02 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	philo_wait(t_philo *philo, size_t until)
{
	while (get_ms_from(philo->sim->start_time) < until && philo->alive)
	{
		pthread_mutex_lock(philo->mutex);
		philo->alive = philo->sim->progress > 0;
		pthread_mutex_unlock(philo->mutex);
		usleep(300);
	}
}
