/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:44:51 by sangkkim          #+#    #+#             */
/*   Updated: 2022/08/26 15:32:43 by sangkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/time.h>

size_t	get_ms_from(struct timeval from)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec - from.tv_sec) % 1000000 * 1000;
	time += (tv.tv_usec - from.tv_usec) % 1000000 / 1000;
	return (time);
}

int	parse_uint(unsigned int *uint, char *s)
{
	size_t	val;

	if (*s < '0' || '9' < *s)
		return (-1);
	val = 0;
	while ('0' <= *s && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		if (val > UINT_MAX)
			return (-2);
		s++;
	}
	if (*s)
		return (-1);
	*uint = val;
	return (0);
}

char	*ft_strcat(char *dst, char *src)
{
	char	*dst_org;

	dst_org = dst;
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (dst_org);
}

char	*ft_numcat(char *dst, size_t n)
{
	char	buffer[25];
	char	*ptr;

	buffer[24] = '\0';
	ptr = buffer + 23;
	if (n == 0)
		*ptr = '0';
	else
	{
		while (n)
		{
			*ptr = n % 10 + '0';
			n /= 10;
			ptr--;
		}
		ptr++;
	}
	ft_strcat(dst, ptr);
	return (dst);
}

void	print(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(STDOUT_FILENO, str, len);
}
