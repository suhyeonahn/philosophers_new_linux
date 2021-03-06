/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:26:03 by suahn             #+#    #+#             */
/*   Updated: 2021/12/27 18:34:19 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				lfork_id;
	int				rfork_id;
	int				eat_count;
	struct timeval	last_meal;
	pthread_t		t_id;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	int				num_philos;
	int				num_meals;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				died;
	int				all_ate;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	print_status;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_meal;
	pthread_attr_t	attr;
	t_philo			philo[250];
	struct timeval	beginning;
	struct timeval	now;
}	t_rules;

void		create_threads(t_rules *rules);
void		*thread(void *philo);
int			eat(t_philo *p);
void		destroy(t_rules *rules);

void		death(t_rules *rules, int i);
void		stop_checker(t_rules *rules);

long long	timestamp(struct timeval t);
int			print_status(t_philo *p, int id, char *str, int status);
void		print_fork(t_philo *p, int id, char *str, int fork);
void		print_eat(t_philo *p, int id, char *str);
void		print_sleep(t_philo *p, int id, char *str);
void		print_think(t_philo *p, int id, char *str);
void		print_die(t_philo *p, int id, char *str);

void		red(void);
void		yellow(void);
void		blue(void);
void		purple(void);
void		white(void);
void		reset(void);

void		init_philos(t_rules *rules);
int			init_mutex(t_rules *rules);
int			init_rules(t_rules *rules);

int			parse_args(int argc, char **argv, t_rules *rules);

size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);

#endif
