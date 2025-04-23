/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:08:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/04/23 15:30:20 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*ft_routine()
{
	printf("Hello World!\n");
	return (NULL);
}

int	main()
{
	pthread_t t1;
	pthread_create(&t1, NULL, &ft_routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}
