#include "../includes/philo.h"

long long	timestamp(struct timeval    t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_fork(t_philo *p, int id, char *str, int fork)
{
	white();
	printf("%lli ms ", timestamp(p->rules->now) - timestamp(p->rules->beginning));
	printf("%i ", id + 1);
    printf("%s", str);
    printf("%d fork\n", fork);
	reset();
}

void	print_eat(t_philo *p, int id, char *str)
{
	purple();
	printf("%lli ms ", timestamp(p->rules->now) - timestamp(p->rules->beginning));
	printf("%i ", id + 1);
    printf("%s", str);
	p->eat_count++;
	reset();
}

void	print_sleep(t_philo *p, int id, char *str)
{
	blue();
	printf("%lli ms ", timestamp(p->rules->now) - timestamp(p->rules->beginning));
	printf("%i ", id + 1);
    printf("%s", str);
	reset();
}

void	print_think(t_philo *p, int id, char *str)
{
	yellow();
	printf("%lli ms ", timestamp(p->rules->now) - timestamp(p->rules->beginning));
	printf("%i ", id + 1);
    printf("%s", str);
	reset();
}

int	print_die(t_philo *p, int id, char *str)
{
	red();
	printf("%lli ms ", timestamp(p->rules->now) - timestamp(p->rules->beginning));
	printf("%i ", id + 1);
    printf("%s", str);
	p->rules->died = 1;
	reset();
	pthread_mutex_unlock(&(p->rules->check_death));
	return (0);
}

int	print_status(t_philo *p, int id, char *str, int status)
{
	pthread_mutex_lock(&(p->rules->check_death));
	if (p->rules->died || p->rules->all_ate)
	{
		pthread_mutex_unlock(&(p->rules->check_death));
		return (0);
	}
	pthread_mutex_lock(&(p->rules->print_status));	
	gettimeofday(&p->rules->now, NULL);	
    if (status > 0)
		print_fork(p, id, str, status);
	else if (status == -33)
		print_eat(p, id, str);
	if (status == -77)
		print_sleep(p, id, str);
	else if (status == -99)
		print_think(p, id, str);
	else if (status == -444)
		print_die(p, id, str);
	pthread_mutex_unlock(&(p->rules->check_death));
	pthread_mutex_unlock(&(p->rules->print_status));
	return (1);
}