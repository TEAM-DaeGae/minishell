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


void			free_double_arr(char **arr);


// builtin functions
int				exec_builtin(char **cmdline);
int				env(char **envp);
void			pwd(void);
void			echo(char **program);


#endif