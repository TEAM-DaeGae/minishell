#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./Libft/libft.h"

#define EXIT_SHELL_SUCCESS 1
#define EXIT_SHELL_FAILURE 0

t_list	*g_proc_list; // parse_proc에서 복사함

typedef struct	s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
}				t_cmd;

/*
** i: input index
** j: buff index
** k: cmdline index
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

void	*parse(char *input_temp);
t_list	*parse_all(char *input, t_data *data, t_list *head);
void	add_node(t_data *data, t_list *head, char *input, int symbol);
void	put_buff_into_cmdline(t_data *data);
void	*initialize(char *input, t_data *data, t_list **head);
int		count_token(char *input);

int		check_white_space(char *input);

void	parse_proc(t_list *proc);
t_list	*ft_exec_proc(t_list *cur_node);
int		ft_exec_builtin(cur_node)