#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Libft/libft.h"

#define EXIT_SHELL_SUCCESS 1
#define EXIT_SHELL_FAILURE 0

# define SYNTAX_ERROR "Syntax error: unexpected token!"
# define QUOTE_ERROR "The number of Quotes is odd!"
# define MEMORY_ERROR "Memory leaks!"
# define PIPE_ERROR "Pipe function is failed!"
# define FORK_ERROR "Fork function is failed!"

t_list	*g_proc_list; // parse_proc에서 복사함
int		g_parse_error = 1; // 1이면 정상, 0이면 에러 발생

typedef struct	s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
}				t_cmd;

/*
** i: input index | j: buff index | k: cmdline index
*/
typedef struct	s_data
{
	t_list	*lstlast;
	t_cmd	*cmd;
	char	*buff;
	int		i;
	int		j;
	int		k;
}				t_data;

/* libft.h 중복
typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
*/

void	parse(char *input_temp);
void	parse_all_char(char *input, t_data *data, t_list *head);
void	add_node(t_data *data, t_list *head, char *input, int symbol);
void	put_buff_into_cmdline(t_data *data);
void	*initialize(char *input, t_data *data, t_list **head);
int		count_token(char *input);

int		check_white_space(char *input);

void	exec_proc(t_list *proc);
int		ft_exec_builtin(t_list *cur_node);

// parse_error.c
void    parse_error(t_data *ptr1, t_list *ptr2, char *comment);
void	free_cmdline(void *content);
void	free_double_str(char **ptr);
