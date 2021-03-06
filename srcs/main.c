/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:49:35 by suahn             #+#    #+#             */
/*   Updated: 2021/12/27 18:01:13 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy(t_rules *rules)
{
	int	i;

	pthread_attr_destroy(&rules->attr);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_join(rules->philo[i].t_id, NULL);
		i++;
	}
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_status);
	pthread_mutex_destroy(&rules->check_death);
	pthread_mutex_destroy(&rules->check_meal);
	pthread_exit(NULL);
}

int	eat(t_philo *p)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(p->rules->forks[p->lfork_id]));
	ret = print_status(p, p->id, "has ", p->lfork_id + 1);
	if (p->rules->num_philos == 1)
	{
		pthread_mutex_unlock(&(p->rules->forks[p->lfork_id]));
		return (0);
	}
	pthread_mutex_lock(&(p->rules->forks[p->rfork_id]));
	ret = print_status(p, p->id, "has ", p->rfork_id + 1);
	pthread_mutex_lock(&(p->rules->check_meal));
	ret = print_status(p, p->id, "is eating\n", -33);
	pthread_mutex_unlock(&(p->rules->check_meal));
	usleep(p->rules->time_to_eat);
	pthread_mutex_unlock(&(p->rules->forks[p->lfork_id]));
	pthread_mutex_unlock(&(p->rules->forks[p->rfork_id]));
	return (ret);
}

void	*thread(void *philo)
{
	t_philo	*p;
	t_rules	*rules;

	p = (t_philo *)philo;
	rules = p->rules;
	while (1)
	{
		if (!eat(p))
			break ;
		if (!print_status(p, p->id, "is sleeping\n", -77))
			break ;
		usleep(p->rules->time_to_sleep);
		if (!print_status(p, p->id, "is thinking\n", -99))
			break ;
	}
	pthread_exit(NULL);
}

void	create_threads(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	philo = rules->philo;
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&(philo[i].t_id),
				&rules->attr, thread, (void *)&philo[i]) < 0)
			exit (0);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		ret;

	ret = parse_args(argc, argv, &rules);
	if (ret < 0)
	{
		write(1, "Error: Wrong argument(s)\n", 25);
		exit (0);
	}
	ret = init_rules(&rules);
	if (ret < 0)
	{
		write(1, "Error: Initialization failed\n", 29);
		exit (0);
	}
	create_threads(&rules);
	stop_checker(&rules);
	destroy(&rules);
}
