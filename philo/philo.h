/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:05:53 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/26 15:37:38 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_arg	t_arg;
typedef struct s_philo	t_philo;
typedef struct s_sim	t_sim;

struct s_arg
{
	size_t				philo_num;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					option;
	size_t				must_eat;
};

struct s_philo
{
	size_t				id;
	size_t				deadline;
	size_t				eat_cnt;
	int					alive;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*mutex;
	struct timeval		start_time;
	t_arg				arg;
	pthread_t			tid;
	t_sim				*sim;
};

struct s_sim
{
	t_arg				arg;
	long long			progress;
	struct timeval		start_time;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*forks;
	t_philo				*philos;
};

// utils.c
size_t	get_ms_from(struct timeval from);
int		parse_uint(unsigned int *uint, char *s);
char	*ft_strcat(char *dst, char *src);
char	*ft_numcat(char *dst, size_t n);
void	print(char *str);

#endif
