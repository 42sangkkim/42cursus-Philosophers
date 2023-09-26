/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:23:36 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/26 15:32:53 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_echo_take_fork(size_t time, size_t id)
{
	char	buffer[100];

	buffer[0] = '\0';
	ft_numcat(buffer, time);
	ft_strcat(buffer, "ms philo ");
	ft_numcat(buffer, id);
	ft_strcat(buffer, " has taken a fork\n");
	print(buffer);
}

void	philo_echo_eat(size_t time, size_t id)
{
	char	buffer[100];

	buffer[0] = '\0';
	ft_strcat(buffer, "\033[0;32m");
	ft_numcat(buffer, time);
	ft_strcat(buffer, "ms philo ");
	ft_numcat(buffer, id);
	ft_strcat(buffer, " is eating\n");
	ft_strcat(buffer, "\033[0;0m");
	print(buffer);
}

void	philo_echo_sleep(size_t time, size_t id)
{
	char	buffer[100];

	buffer[0] = '\0';
	ft_numcat(buffer, time);
	ft_strcat(buffer, "ms philo ");
	ft_numcat(buffer, id);
	ft_strcat(buffer, " is sleeping\n");
	print(buffer);
}

void	philo_echo_think(size_t time, size_t id)
{
	char	buffer[100];

	buffer[0] = '\0';
	ft_numcat(buffer, time);
	ft_strcat(buffer, "ms philo ");
	ft_numcat(buffer, id);
	ft_strcat(buffer, " is thinking\n");
	print(buffer);
}

void	philo_echo_die(size_t time, size_t id)
{
	char	buffer[100];

	buffer[0] = '\0';
	ft_strcat(buffer, "\033[0;31m");
	ft_numcat(buffer, time);
	ft_strcat(buffer, "ms philo ");
	ft_numcat(buffer, id);
	ft_strcat(buffer, " died\n");
	ft_strcat(buffer, "\033[0;0m");
	print(buffer);
}
