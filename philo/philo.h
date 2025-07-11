/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:15:41 by thodavid          #+#    #+#             */
/*   Updated: 2025/06/18 14:58:59 by thodavid         ###   ########.fr       */
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

/*___________________________LOG___________________________________**/

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define RESET	"\e[0m"


/*___________________________STRUCT________________________________**/

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
	pthread_mutex_t	mutex;

}	t_fork;

struct	s_data
{
	int		number_of_philos;
	int		death;
	long	start;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	pthread_mutex_t	print_mutex;
	t_fork	*forks_arr;
	t_philo	*philos_arr;
};





/*___________________________MAIN______________________________________**/
t_data	*ft_parsing(int ac, char **av);
int		ft_free_thread_tab(pthread_t *arr, int p);
/*___________________________PARSING___________________________________**/
t_data	*ft_stock_data(char **av);
t_philo	*ft_philo_arr_init(int nbr_philo, t_data	*table);
void	ft_check_args(char **av);
void	ft_check_data(t_data *data);
void    fork_mutex_init(t_data *data);

/*___________________________UTILS_____________________________________**/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_error(char *str);
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
char    *log_format(int philo_id);
void    ft_log(t_philo *philo, char *msg);

/*___________________________TIMESTAMP_________________________________**/
long	get_timestamp_ms(void);
long	timestamp_now(t_data *data);
/*___________________________THREAD____________________________________**/
pthread_t *ft_thread(t_data *data, void *f());
void	*philo_life(void *arg);
void *ft_thread_death_check(void *arg);
void    ft_eating(t_philo *philo);
void    ft_thinking(t_philo *philo);
void    ft_sleeping(t_philo *philo);
void    ft_take_forks(t_philo *philo);

#endif
