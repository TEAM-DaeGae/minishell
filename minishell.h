/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 19:04:46 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/06 07:40:20 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// gaekim.h 시작 (setup 전 까지)
extern t_list *g_proc_list;
extern int g_parse_error; // 1이면 정상, -1이면 에러 발생

#define SYNTAX_ERROR "Syntax error: near unexpected token!"
#define QUOTE_ERROR "The number of Quotes is odd!"
#define MALLOC_ERROR "Memory malloc fail!"
#define PIPE_ERROR "Pipe function is failed!"
#define FORK_ERROR "Fork function is failed!"

typedef struct s_cmd
{
	char	**cmdline;
	int		flag; // 0 = semicolon or NULL, 1 = pipe
	char	quote;
	int		has_redir; // 1 = redir 최소 1개 있다. 0 = redir 아예 없다.
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

# define BREDIR	60
# define REDIR	62
# define DREDIR	6
// BREDIR = '<', REDIR = '>', DREDIR = >>

typedef struct	s_redir
{
	int			argc; // redir 기호 개수 + 1 (>>는 2개로 카운트)
	char		**argv;
	char		**cmds;
	char		*types;
}				t_redir;

// exec_redir.c
void		init_redir(char *command, t_redir *re);
int			parse_redir_final(t_redir *r, int j);
int			parse_redir(char *command, t_redir *r);
void		open_unnecessary_files(t_redir *r);
void    exec_redir(char **cmdline);

// utils_redir2.c
char    *ft_strjoin_c(char *s, char c);
char    *change_from_double_to_single_cmdline(char **cmdline);
char	*remove_single_quotes(char *str);

// cmd_redir.c
void			cmd_redir(t_redir *r);

// utils_redir.c
int		is_single_redir(char *command, int i);
int		find_redir_type(char *command, int i);
int		has_redir_syntax_error(char *str);
int		ft_puterror_fd(char *s1, char *s2, int fd);
char	*substr_and_trim(char *command, int start, int num, char *charset);
void	free_double_arr(char **arr);

// parser.c
void	*parse(char *input_temp);
void	parse_all_char(char *input, t_data *data, t_list *head);
int		add_node(t_data *data, t_list *head, char *input, int symbol);
void	put_buff_into_cmdline(t_data *data);
void	exec_proc(t_list *proc);

// utils_parse.c
void	*initialize(char *input, t_data *data, t_list **head);
int		count_token(char *input);
int		check_white_space(char *input);

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
