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

extern char **g_envp;
extern int g_exit_status;

# define MAXSIZE    1024

# define FALSE      0
# define TRUE       1 

# define ERROR      -1
# define SUCCESS    1

# define STDIN      0
# define STDOUT		1
# define STDERR		2

// # define EXIT_SUCCESS 1
// # define EXIT_FAILURE 0

//gaekim.h ~ setup 전 까지
extern t_list *g_proc_list;
extern int g_parse_error;

#define SYNTAX_ERROR "Syntax error: near unexpected token!"
#define QUOTE_ERROR "The number of Quotes is odd!"
#define MALLOC_ERROR "Memory malloc fail!"
#define PIPE_ERROR "Pipe function is failed!"
#define FORK_ERROR "Fork function is failed!"

typedef struct s_cmd
{
	char	**cmdline;  
	int		flag; 
	char	quote;
	int 	fds[2];
} 				t_cmd;

/*
** i: input index | j: buff index | k: cmdline index
*/
typedef struct s_data
{
	t_list	*lstlast;
	t_cmd 	*cmd;
	char 	*buff;
	int 	i;
	int 	j;
	int		k;
}				t_data;

/* libft.h 중복
typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
*/

// parser.c
void	*parse(char *input_temp);
void	parse_all_char(char *input, t_data *data, t_list *head);
void	add_node(t_data *data, t_list *head, char *input, int symbol);
void	put_buff_into_cmdline(t_data *data);
void	*initialize(char *input, t_data *data, t_list **head);
int		count_token(char *input);
int		check_white_space(char *input);
void	exec_proc(t_list *proc);

// parse_error.c
void	*parse_error(t_data *ptr1, t_list *ptr2, char *comment);
void	free_cmdline(void *content);
void	free_double_str(char **ptr);

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
int 			check_builtin(char **cmdline);
int 			exec_builtin(char **cmdline);
int 			exec_cmds(t_list *cur_proc, t_cmd *cmd);

int 			ft_env(char **envs);
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
