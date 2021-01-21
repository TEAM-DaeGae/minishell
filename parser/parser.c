#include "minishell_gaekim.h"

int		count_token(char *input)
{
	int		count_token;
	char	*p;

	count_token = 1;
	if (!(p = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (0);
	ft_strcpy(p, input);
	if (ft_strtok(p, ' ') != NULL)
	{
		while (ft_strtok(NULL, ' ') != NULL)
			count_token++;
	}
	free(p);
	return (count_token);
}

void	*initialize(char *input, t_data *data, t_list **head)
{
	*head = ft_lstnew(NULL);
	data->lstlast = *head;

	if (!(data->cmd = ft_calloc(1, sizeof(t_cmd))))
		return ((void *)0);
	if (!(data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *)))) // 보류: char**이 calloc으로 가능?
		return ((void *)0);
	data->cmd->flag = 0;
	data->cmd->quote = 0;

	if (!(data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return ((void *)0);
	data->i = 0;
	data->j = 0;
	data->k = 0;

	return (0); // 에러함수 추가하면 지우기
}

void	put_buff_into_cmdline(t_data *data)
{
	if (*(data->buff) == 0)
		return ;
	
	data->cmd->cmdline[(data->k)] = ft_strdup(data->buff);
	data->cmd->cmdline[(data->k) + 1] = NULL;
	(data->k)++;

	ft_bzero(data->buff, ft_strlen(data->buff) + 1);
	data->j= 0;
}

void	add_node(t_data *data, t_list *head, char *input, int symbol)
{
	data->cmd->flag = symbol;
	data->k = 0;
	if (symbol == 4)
		data->i++;

	if (*(data->buff))
		put_buff_into_cmdline(data);

	ft_lstadd_back(&head, ft_lstnew(data->cmd));
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *));
	data->lstlast = ft_lstlast(head);
}

int		ft_exec_builtin(cur_node)
{
	t_cmd	*cmdline;

	cmdline = (t_cmd *)(cur_node->content->cmdline);
	if (!ft_strcmp(cmdline[0], "echo"))
		ft_echo(cmdline);
	else if (!ft_strcmp(cmdline[0], "cd"))
		ft_cd(cmdline, g_envp);
	else if (!ft_strcmp(cmdline[0], "pwd"))
		ft_pwd());
	else if (!ft_strcmp(cmdline[0], "env"))
		ft_env(cmdline, g_envp);
	else if (!ft_strcmp(cmdline[0], "export"))
		ft_export(cmdline, g_envp);
	else if (!ft_strcmp(cmdline[0], "unset"))
		ft_unset(cmdline, g_envp);
	else if (!ft_strcmp(cmdline[0], "exit"))
		ft_exit(cmdline);
	else
	{
		//free_linked_list(cmdline);
		return (0);
	}
	return (1);
}

t_list	*ft_exec_proc(t_list *cur_node)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(cur_node->content);
	if (cmd->flag == 1)
		return (ft_exec_builtin(cur_node));
	else if (cmd->flag == 2)
		return (ft_pipe(cur_node));
	else
		return (cur_node);
}

void	parse_proc(t_list *proc)
{
	t_list	*cur_node;
	t_cmd	*cmd;
	char	buff[1000];

	g_proc_list = proc;
	cur_node = proc->next; // why ?
	while (cur_node)
	{
		cmd = (t_cmd *)(cur_node->content);
		//cmd->program = parse_program();
		cur_node = ft_exec_proc(cur_node);
	}
}

t_list	*parse_all(char *input, t_data *data, t_list *head)
{
	while (input[data->i])
	{
		if (data->cmd->quote == input[data->i])
			data->cmd->quote = 0;
		else if (data->cmd->quote == 0 && (data->cmd->quote == '\'' || input[data->i] == '\"'))
			data->cmd->quote = input[data->i];
		else if (data->cmd->quote == 0 && input[data->i] == ' ')
			put_buff_into_cmdline(data);
		else if (data->cmd->quote == 0 && (input[data->i] == ';' || input[data->i] == 0))
			add_node(data, head, input, 1);
		else if (data->cmd->quote == 0 && input[data->i] == '|')
			add_node(data, head, input, 2);
		else
			data->buff[data->j++] = input[data->i];
		data->i++;
	}
	return (head);
}

void	*parse(char *input_temp)
{
	t_data	data;
	t_list	*head;
	char	*input;

	input = ft_strtrim(input_temp, " ");
	initialize(input, &data, &head);
	head = parse_all(input, &data, head);
	parse_proc(head);
	if (*(data.buff))
		put_buff_into_cmdline(&data);
	free(input);
	free(data.buff);
	return (head);
}

int		check_white_space(char *input)
{
	int	space;
	int	i;

	space = 0;
	i = 0;
	if (input[0] == NULL)
		return (1);
	while (input[i])
	{
		if (input[i] == '\r' || input[i] == '\v'
			|| input[i] == '\t' || input[i] == '\f')
			return (1);
		else if (input[i] == ' ')
			space++;
		i++;
	}
	if (space == (int)ft_strlen(input))
		return (1);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	//g_envp = copy_envp(envp);
	//set_signal();
	//show_daegae();
	while (1)
	{
		//show_prompt();
		get_next_line(0, &input);

		if (!check_white_space(input))
			parse(input); // 파싱함수 첫 진입

		free(input);
	}
	return (0);
}