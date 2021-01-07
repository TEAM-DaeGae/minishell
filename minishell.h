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

char    **g_envp;

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

t_list		*init_envs(int argc, char **argv, char **envp);

#endif