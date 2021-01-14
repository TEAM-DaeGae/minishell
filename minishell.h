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

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
}				t_cmd;

typedef struct	s_data
{
	t_list	*lst;
	t_cmd	*cmd;
	char	*buff;
	int		i;
	int		j;
	int		k;
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
char			*find_path(char *cmdline, char **envs);

// exec
void			exec_cmds(char **cmdline);
void			exec_bin(char **cmdline);
int				exec_builtin(char **cmdline);
int				ft_env(char **envs);
void			ft_pwd(void);
void			ft_echo(char **cmdline);
void			ft_cd(char **cmdline, char **envs);
void			ft_exit(char **cmdline);
int		    	ft_export(char **cmdline);
int				ft_unset(char **cmdline);



// errors
int				ft_puterror_fd(char *s1, char *s2, int fd);


#endif