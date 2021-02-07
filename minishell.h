/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:56:32 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/08 01:34:46 by gaekim           ###   ########.fr       */
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

# define MAXSIZE		1024

# define FALSE			0
# define TRUE			1

# define ERROR			-1
# define SUCCESS 		1

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

# define COLOR_BR_BLUE	"\033[34;1m"
# define COLOR_WHITE	"\033[37m"
# define COLOR_CYAN		"\033[36m"
# define END_COLOR		"\033[0m"

# define SYNTAX_ERROR	"Syntax error: near unexpected token!"
# define QUOTE_ERROR 	"The number of Quotes is odd!"
# define MALLOC_ERROR 	"Memory malloc fail!"
# define PIPE_ERROR 	"Pipe function is failed!"
# define FORK_ERROR 	"Fork function is failed!"

# define BREDIR			60
# define REDIR			62
# define DREDIR			6

extern char		**g_envp;
extern int		g_exit_status;
extern int		g_parse_error;

typedef struct	s_redir
{
	int			argc;
	char		**argv;
	char		**cmds;
	char		*types;
}				t_redir;

typedef struct	s_cmd
{
	char		**cmdlines;
	int			flag;
	int			preflag;
	char		quote;
	int			fds[2];
	int			has_redir;
}				t_cmd;

/*
** i: input index | j: buff index | k: cmdline index
*/
typedef	struct	s_data
{
	t_list		*lstlast;
	t_cmd		*cmd;
	char		*buff;
	int			i;
	int			j;
	int			k;
}				t_data;

/*
** exec_redir.c
*/
void			init_redir(char *command, t_redir *re);
int				parse_redir_final(t_redir *r, int j);
int				parse_redir(char *command, t_redir *r);
void			open_unnecessary_files(t_redir *r);
void			exec_redir(t_cmd *cmd, char **cmdline);

/*
** utils_redir2.c
*/
char			*ft_strjoin_c(char *s, char c);
char			*change_from_double_to_single_cmdline(char **cmdline);
char			*remove_single_quotes(char *str);

/*
** cmd_redir.c
*/
void			cmd_redir(t_cmd *cmd, t_redir *r);

/*
** utils_redir.c
*/
int				is_single_redir(char *command, int i);
int				find_redir_type(char *command, int i);
int				has_redir_syntax_error(char *str);
int				ft_puterror_fd(char *s1, char *s2, int fd);
char			*substr_and_trim(char *command, int start, int num, \
									char *charset);
void			free_double_arr(char **arr);

/*
** parser.c
*/
void			*parse(char *input_temp);
void			parse_all_char(char *input, t_data *data, t_list *head);
int				add_node(t_data *data, t_list *head, char *input, int symbol);
void			put_buff_into_cmdline(t_data *data);

/*
** utils_parse.c
*/
void			*initialize(char *input, t_data *data, t_list **head);
int				count_token(char *input);
int				check_white_space(char *input);

/*
** parse_error.c
*/
void			*parse_error(t_data *ptr1, t_list *ptr2, char *comment);
void			free_cmdline(void *content);
void			free_double_str(char **ptr);

/*
** main.c
*/
char			**copy_envp(char **envs);
void			show_prompt(void);
void			show_daegae(void);

/*
** utils_signal.c
*/
void			set_signal(void);
void			handle_signal(int signo);

/*
** utils_envv.c
*/
char			*find_value(char *key, char **envs);
void			free_double_arr(char **arr);
char			*find_path(char *cmdline, char **envs);

/*
** utils_execute.c
*/
int				heck_builtin(char **cmdline);
int				remove_char(char *str, char c);
int				check_export(char *str, char ***envs);

/*
** execute/
*/
void			exec_process(t_list *proc);
int				exec_builtin(t_cmd *cmd, char **cmdline);
int				exec_pipe(t_list *cur_proc, t_cmd *cmd);
void			exec_child_process(t_cmd *cmd, t_cmd *next_cmd);

void			ft_env(char **envs);
void			ft_pwd(void);
void			ft_cd(char **cmdline, char **envs);
void			ft_echo(char **cmdline, char **g_envp);
void			ft_exit(t_cmd *cmd, char **cmdline);
void			ft_export(t_cmd *cmd, char **cmdline);
void			ft_unset(t_cmd *cmd, char **cmdline);

/*
** errors/
*/
void			print_errno_err(char *err_msg);
int				print_execute_err_1(char *token, char *err_msg);
int				print_execute_err_2(char *token1, char *token2, char *err_msg);
void			print_identifier_err(char *token1, char *token2);

#endif
