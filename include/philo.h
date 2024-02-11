/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:39 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:59:24 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*	COLOR	*/
#define COLOR_RESET "\033[0m"
#define COLOR_ROSE "\033[38;5;213m" // Rose n'est pas standard, utiliser un code approximatif
#define COLOR_LILAC "\033[38;5;183m" // Lilas, aussi approximatif
#define COLOR_VIOLET "\033[35m" // Violet standard
#define COLOR_GREEN "\033[32m" // Vert standard
#define COLOR_CYAN "\033[36m" // Cyan pour un bon contraste avec le reste

/*	Bool	*/
# define TRUE 1
# define FALSE 0

/*	Help	*/
# define HELP "The number of argments must be 4 or 5:\n\
- arg1 number of philosophers\n\
- arg2 time to die\n\
- arg3 time to eat\n\
- arg4 time to sleep\n\
- arg5 number of times each philosopher must eat (optional)"

/*	Routines messages	*/
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

/*	Structures	*/
typedef struct s_input
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_eat;
}					t_input;

typedef struct s_fork
{
	int				left;
	int				right;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				done;
	int				num_of_times_ate;
	int				order;
	long long		time_to_die;
	t_fork			fork;
	pthread_t		thread;
	pthread_mutex_t	reset;
	pthread_mutex_t	ate;
}					t_philo;

typedef struct s_main
{
	int				n_thread;
	int				philo_dead;
	int				philo_ate;
	long long		t0;
	t_input			input;
	t_philo			*philo;
	pthread_t		orchestrator;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	index;
	pthread_mutex_t	dead;
}					t_main;

/*	ft_actions.c	*/
int			philo_eat(t_main *main, int i);
int			philo_sleep(t_main *main, int i);
int			philo_think(t_main *main, int i);
int			philo_is_dead(t_main *main, int *i);
int			drop_forks(t_main *main, int i);

/*	ft_errors.c	*/
int			ft_errors(int argc, char **argv, t_main *main);
int			init_input_struct(int argc, char **argv, t_main *main);
void		print_args_errors(t_main *main, int argc);

/*	ft_forks.c	*/
int			create_forks(t_main *main);
void		unlock_forks(t_main *main);

/*	ft_philos.c	*/
int			create_philos(t_main *main);
void		init_philo_struct(t_main *main, int i, int j);

/*	ft_threads.c	*/
int			create_threads(t_main *main);
int			join_threads(t_main *main);
int			destroy_threads(t_main *main);

/*	ft_time.c	*/
long long	get_time(void);
long long	delta_time(long long time2);
void		exec_action(long long time);

/*	main.c	*/
int			main(int argc, char **argv);
int			one_philo(t_main *main);

/*	ft_utils.c	*/
int			ft_atoi(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(const char *str);
void		ft_free(t_main *main);
const char* get_philo_color(int color_index);
/*	ft_routine.c	*/
void		*routine(void *args);
int			routine_execute(t_main *main, int i);
void		*checker(void *args);
int			philo_print(t_main *main, int id, char *status);

#endif