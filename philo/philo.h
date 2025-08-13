/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:15:41 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/13 12:36:54 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

/*___________________________STRUCT________________________________**/

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	int		pthread_id;
	int		left_fork;
	int		right_fork;
	int		meals_eat;
	int		is_full;
	long	last_meal;
	t_data	*data;
}	t_philo;

typedef struct s_fork
{
	int										id;
	pthread_mutex_t							mutex;
}	t_fork;

struct	s_data
{
	int					number_of_philos;
	int					max_meal;
	int					max_meal_activ;
	int					full_philo_count;
	int					death;
	int					stop;
	long				start;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	t_fork				*forks_arr;
	t_philo				*philos_arr;
	pthread_t			*threads_arr;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		state_mutex;
};

/*___________________________PARSING___________________________________**/
t_data	*parsing(int ac, char **av);
t_data	*stock_data(char **av);
t_philo	*philo_arr_init(int nbr_philo, t_data	*table);
int	fork_mutex_arr_init(t_data *data);

/*_______________________PARSING_UTILS_________________________________**/
int		check_args(int ac, char **av);
int		check_data(t_data *data);

/*___________________________UTILS_____________________________________**/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

/*_______________________free_data_________________________________**/
int		free_mutex_tab(t_fork *arr, int p);
int		free_thread_tab(pthread_t *arr, int p);

/*___________________________LOG_____________________________________**/
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *str);
void	print_death(t_philo *philo, long now);
void	ft_log(t_philo *philo, char *msg);

/*___________________________TIMESTAMP_________________________________**/
long	get_timestamp_ms(void);
long	timestamp_now(long start);

/*___________________________THREAD____________________________________**/
void	handle_single_philo(t_philo *philo, pthread_t death_checker);
void	philo_loop(t_philo *philo);
void	*philo_routine(void *arg);
void	*thread_death_check(void *arg);
pthread_t	*thread_arr_init(t_data *data, void *f());

/*___________________________LIFE____________________________________**/
void	ft_eating(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_sleeping(t_philo *philo);

/*___________________________FORKS____________________________________**/
void	ft_put_down_fork(t_philo *philo);
int		handle_even_philo(t_philo *philo, int l, int r);
int		handle_odd_philo(t_philo *philo, int l, int r);
int		ft_take_forks(t_philo *philo);
#endif
