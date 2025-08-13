/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:03:23 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/12 12:35:02 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (nptr[0] == '\0')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (r > (INT_MAX - (nptr[i] - '0')) / 10)
			return (-1);
		r = (r * 10) + (nptr[i] - '0');
		i++;
	}
	return (r);
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	if (nptr[0] == '\0')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (r > (LONG_MAX - (nptr[i] - '0')) / 10)
			return (-1);
		r = (r * 10) + (nptr[i] - '0');
		i++;
	}
	return (r);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
