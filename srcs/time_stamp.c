/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:38:29 by thodavid          #+#    #+#             */
/*   Updated: 2025/08/08 11:03:10 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
long get_timestamp_ms(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        ft_error("φ gettimeofday() failed φ");
    return tv.tv_sec * 1000L + tv.tv_usec / 1000;
}


long	timestamp_now(long start)
{
	long			ts_now;

	ts_now = (get_timestamp_ms() - start);
	return (ts_now);
}
