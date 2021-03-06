/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:32:08 by suahn             #+#    #+#             */
/*   Updated: 2021/12/27 18:38:31 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	death(t_rules *rules, int i)
{
	gettimeofday(&rules->now, NULL);
	if ((timestamp(rules->now) - timestamp(rules->philo[i].last_meal))
		> (rules->time_to_die / 1000))
	{
		if (!print_status(&rules->philo[i],
				rules->philo[i].id, "has died\n", -444))
			return ;
	}
}

void	stop_checker(t_rules *rules)
{
	int	i;
	int	ate;

	while (!rules->died)
	{
		i = 0;
		ate = 0;
		while (i < rules->num_philos)
		{
			pthread_mutex_lock(&(rules->check_meal));
			death(rules, i);
			if (rules->num_meals
				&& rules->philo[i].eat_count >= rules->num_meals)
				ate++;
			pthread_mutex_unlock(&(rules->check_meal));
			i++;
			if (rules->num_meals && ate >= rules->num_philos)
			{
				pthread_mutex_lock(&(rules->check_meal));
				rules->all_ate = 1;
				pthread_mutex_unlock(&(rules->check_meal));
				return ;
			}
		}
	}
}
