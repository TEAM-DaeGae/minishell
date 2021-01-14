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
# define FALSE 0
# define TRUE 1 
# define ERROR 0
# define SUCCESS 1

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

//setup
void    		set_signal(void);
char			**copy_envp(char **envs);
void            show_prompt(void);
void        	show_daegae(void);
void			handle_signal(int signo);
void			handle_child_signal(int signo);

// utils_exec.c
char			*find_value(char *key, char **envs);
void			free_double_arr(char **arr);
char			*find_path(char *progam, char **envs);

// exec
void			exec_cmds(char **cmdline);
void			exec_bin(char **program);
int				exec_builtin(char **program);
int				ft_env(char **envs);
void			ft_pwd(void);
void			ft_echo(char **program);
void			ft_cd(char **program, char **envs);
void			ft_exit(char **program);
int		    	ft_export(char **program);
int				ft_unset(char **program);



// errors
int				ft_puterror_fd(char *s1, char *s2, int fd);


#endif