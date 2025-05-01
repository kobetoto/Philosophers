/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:15:41 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/01 14:42:05 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	int		pthread_id;
	int		left_fork;
	int		right_fork;
	long	last_meal;
	t_data	*data;

}	t_philo;

typedef struct s_fork
{
	int			id;
	pthread_t	mutex;

}	t_fork;

struct	s_data
{
	int		number_of_philos;
	int		max_meal;
	long	start;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	t_fork	*forks_arr;
	t_philo	*philos_arr;
};

t_data	ft_parsing(int ac, char **av);
t_data	ft_stock_data(char **av);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_error(char *str);
void	ft_check_args(char **av);
void	ft_check_data(t_data *data);
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

#endif
