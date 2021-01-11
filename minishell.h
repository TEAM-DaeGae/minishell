#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "Libft/libft.h"

# define MAXSIZE 1024

char    		**g_envp;
int				g_exit_status ;

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef struct	s_data
{
	char		**program; // ex. program = {"ls", "-al", NULL}
	int     flag;
}				t_data;

// utils
void			free_double_arr(char **arr);

// envp
char			*find_value(char *key, char **envs);



// builtin functions
int				exec_builtin(char **cmdline);
int				ft_env(char **envs);
void			ft_pwd(void);
void			ft_echo(char **program);
void			ft_cd(char **program, char **envs);
void			ft_exit(char **argv);

// errors
int				ft_puterror_fd(char *s1, char *s2, int fd);


#endif