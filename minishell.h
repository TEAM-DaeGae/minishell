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

# define MAXSIZE    1024

# define FALSE      0
# define TRUE       1 

# define ERROR      -1
# define SUCCESS    1

# define STDIN      0
# define STDOUT		1
# define STDERR		2

extern 	char **g_envp;
extern 	int  g_exit_status;

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
int			    ft_cd(char **cmdline, char **envs);
void			ft_exit(char **cmdline);
int		    	ft_export(char **cmdline);
int	            check_export(char *str, char ***envs);
int				ft_unset(char **cmdline);


// errors
void	        print_errno_err(char *err_msg);
int		        print_execute_err_1(char *token, char *err_msg);
int             print_execute_err_2(char *token1, char *token2, char *err_msg);
void	        print_identifier_err(char *token1, char *token2);


#endif
