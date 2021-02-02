#include "minishell.h"

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
		return ((void *)parse_error(data, NULL, MALLOC_ERROR));
	if (!(data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *)))) // 보류: char**이 calloc으로 가능?
		return ((void *)parse_error(data, NULL, MALLOC_ERROR));
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	if (!(data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return ((void *)parse_error(data, NULL, MALLOC_ERROR));
	data->i = -1;
	data->j = 0;
	data->k = 0;
	return (NULL);
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
	if (*(data->buff))
		put_buff_into_cmdline(data);
	// head에 t_list *p(content:data->cmd, next:NULL)를 복사
	ft_lstadd_back(&head, ft_lstnew(data->cmd));
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *));
	data->lstlast = ft_lstlast(head);
	data->k = 0;	
}

void	exec_proc(t_list *head) // 인자는 연결리스트의 헤드포인터
{
	t_list	*cur_proc;
	t_cmd	*cmd;

	cur_proc  = head->next;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content; // (t_cmd *)형태로 자료형변환을 위해 옮겨담음.
		if (cmd->cmdline[0]) // 명령어가 있으면 실행
		{
			if (check_builtin(cmd->cmdline) == 1)
				exec_builtin(cmd->cmdline);
			else
				exec_cmds(cur_proc, cmd); //flag == 1 이면 파이프, comline == {ls, -al}
		}
		cur_proc = cur_proc->next;

		dprintf(2, "in while\n");
	}
	dprintf(2, "exec_process end \n");
	ft_lstclear(&head, free_cmdline);
}

void	parse_all_char(char *input, t_data *data, t_list *head)
{	
	if (data->cmd->quote == input[data->i])
		data->cmd->quote = 0;
	else if (data->cmd->quote == 0 && (data->cmd->quote == '\'' || input[data->i] == '\"'))
		data->cmd->quote = input[data->i];
	else if (data->cmd->quote == 0 && input[data->i] == ' ')
		put_buff_into_cmdline(data);
	else if (data->cmd->quote == 0 && input[data->i] == ';')
		add_node(data, head, input, 0);
	else if (data->cmd->quote == 0 && input[data->i] == '|')
		add_node(data, head, input, 1);
	else
		data->buff[data->j++] = input[data->i];
}

// parse_error에 가는 상황(에러상황)의 경우, exec_proc으로 안 가고 main함수로 돌아가서 free만 하고 끝내야 한다.
void	*parse(char *input_temp)
{
	t_data	data;
	t_list	*head;
	char	*input;

	input = ft_strtrim(input_temp, " ");
	initialize(input, &data, &head);

	while (input[++(data.i)])
	{
		parse_all_char(input, &data, head);
		if (g_parse_error == 0)
			return (parse_error(&data, head, SYNTAX_ERROR));
	}
	
	if (*(data.buff))
		put_buff_into_cmdline(&data);
	if (data.k)
		ft_lstadd_back(&head, ft_lstnew(data.cmd));
	if (data.cmd->quote != 0)
		parse_error(&data, head, QUOTE_ERROR);
	free(data.buff);

	// g_parse_error == 0인 경우, exec_cmd로 가지 않고 함수 종료.
	if (g_parse_error)
		exec_proc(head);

	return (NULL);
}

int		check_white_space(char *input)
{
	int	space;
	int	i;

	space = 0;
	i = 0;
	if (input[0] == 0)
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