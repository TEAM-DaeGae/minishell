#include "minishell.h"

int g_parse_error;

int		add_node(t_data *data, t_list *head, char *input, int symbol)
{
	data->cmd->flag = symbol;
	if (*(data->buff))
		put_buff_into_cmdline(data);
	if ((data->cmd->cmdline)[0] == 0 && data->cmd->flag <= 1)
		return (ERROR);
	else
	{
		// head에 t_list *p(content:data->cmd, next:NULL)를 복사
		ft_lstadd_back(&head, ft_lstnew(data->cmd));
		data->cmd = ft_calloc(1, sizeof(t_cmd));
		data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *));
		data->lstlast = ft_lstlast(head);
	}
	data->k = 0;
	return (SUCCESS);
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

void	parse_all_char(char *input, t_data *data, t_list *head)
{	
	if (data->cmd->quote == input[data->i])
		data->cmd->quote = 0;
	else if (data->cmd->quote == 0 && (input[data->i] == '\'' || input[data->i] == '\"'))
		data->cmd->quote = input[data->i];
	else if (data->cmd->quote == 0 && input[data->i] == ' ')
		put_buff_into_cmdline(data);
	else if (data->cmd->quote == 0 && input[data->i] == ';')
		g_parse_error = add_node(data, head, input, 0);
	else if (data->cmd->quote == 0 && input[data->i] == '|')
		g_parse_error = add_node(data, head, input, 1);
	else
	{
		if (data->cmd->quote == 0 && ft_strchr("><", input[data->i]))
			data->cmd->has_redir = 1; // 리다이렉션 기호가 최소 1개 있다. 아래에서 기호도 buff에 담아줌.
		else if (data->cmd->quote != '\'' && input[data->i] == '\\' && input[data->i + 1])
			data->i++; // i++해서 escape문자는 담지않고 통과하고, 아래에서 escape 다음문자를 buff에 담아줌.
		data->buff[data->j++] = input[data->i];
	}
}

// parse_error에 가는 상황(에러상황)의 경우, exec_proc으로 안 가고 main함수로 돌아가서 free만 하고 끝내야 한다.
void	*parse(char *input_temp)
{
	t_data	data;
	t_list	*head;
	char	*input;

	input = ft_strtrim(input_temp, " ");
	initialize(input, &data, &head);
	g_parse_error = 1;
	while (input[++(data.i)])
	{
		parse_all_char(input, &data, head);
		if (g_parse_error < 1)
			return (parse_error(&data, head, SYNTAX_ERROR));
	}
	if (*(data.buff))
		put_buff_into_cmdline(&data);
	if (data.k)
		ft_lstadd_back(&head, ft_lstnew(data.cmd));
	if (data.cmd->quote != 0)
		parse_error(&data, head, QUOTE_ERROR);
	free(data.buff);
	// g_parse_error <= 0인 경우, exec_cmd로 가지 않고 함수 종료.
	if (g_parse_error == 1)
		exec_process(head);
	return (NULL);
}
