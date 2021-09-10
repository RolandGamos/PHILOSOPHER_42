/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:11:09 by user42            #+#    #+#             */
/*   Updated: 2021/09/10 14:09:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_millisecond	get_time(t_philo *philo)
{
	t_millisecond	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = to_mili(tv) - philo->args->origin_time;
	return (time);
}

void	philo_sleep(t_philo *philo)
{
	t_millisecond	sleep;
	
	sleep = get_time(philo) + philo->args->time_to_sleep;
	printf("%lu philo %d is sleeping \n", get_time(philo), philo->num);
	while (get_time(philo) < sleep)
 	{
	}
	printf("%lu philo %d is thinking \n", get_time(philo), philo->num);
}

void	philo_death(t_philo *philo)
{

}


void	philo_eat(t_philo *philo)
{
	t_millisecond	eat;

	eat = 0;
	pthread_mutex_lock(&philo->args->mutex[*philo->forks[0]]);
	printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num,* philo->forks[0]);
	pthread_mutex_lock(&philo->args->mutex[*philo->forks[1]]);
	printf("%lu philo %d has taken a fork num %d\n", get_time(philo), philo->num, *philo->forks[1]);
	printf("%lu philo %d is eating\n", get_time(philo), philo->num);
	eat = get_time(philo) + philo->args->time_to_eat;
	philo->death_time = get_time(philo) + philo->args->time_to_die;
	while (get_time(philo) < eat)
 	{
		 if (get_time(philo) > philo->death_time)
		 	philo_death(philo);
	}
	pthread_mutex_unlock(&philo->args->mutex[*philo->forks[0]]);
	pthread_mutex_unlock(&philo->args->mutex[*philo->forks[1]]);
}

void	*philo_routine(void *philo)
{
	t_philo			*new_philo;

	new_philo = (t_philo *)philo;
	while (1)
	{
		philo_eat(new_philo);
		philo_sleep(new_philo);

	}
	 return (NULL);
}
