#include "minishell.h"

void	put_buff_into_cmdline(t_data *data)
{
	if (*(data->buff) == 0)
		return ;
	
	data->cmdline[data->k] = ft_strdup(data->buff);
	data->k++;

	ft_bzero(data->buff, ft_strlen(data->buff) + 1);
	data->j= 0;
}

/*  ** 수정하기 **
t_list	*check_flag(t_list *cur_node) // 각 함수로 이동해서 거기에서 exec_builtin 함수 실행함
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(cur_node->content);
	if (cmd->flag == 0)
		return (ft_semicolon(cur_node));
	else if (cmd->flag == 1)
		return (ft_pipe(cur_node));
	else if (cmd->flag == 2)
		return (redirection(cur_node));
	else if (cmd->flag == 3)
		return (redirection(cur_node));
	else if (cmd->flag == 4)
		return (redirection(cur_node));
	else
		return (cur_node);
}
*/

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
	data->lst = ft_lstlast(head);
}

t_list	*parsing_all(char *input, t_data *data, t_list *head)
{
	while (input[data->i])
	{
		if (data->cmd->quote == input[data->i])
			data->cmd->quote = 0;
		else if (data->cmd->quote == 0 && (data->cmd->quote == '\'' || input[data->i] == '\"'))
			data->cmd->quote = input[data->i];

		else if (data->cmd->quote == 0 && input[data->i] == ' ')
			put_buff_into_cmdline(&data);
		
		else if (data->cmd->quote == 0 && (input[data->i] == ';' || input[data->i] == NULL))
			add_node(data, head, input, 1);
		else if (data->cmd->quote == 0 && input[data->i] == '|')
			add_node(data, head, input, 2);
		else if (data->cmd->quote == 0 && input[data->i] == '>' && input[data->i + 1] != '>')
			add_node(data, head, input, 3);
		else if (data->cmd->quote == 0 && input[data->i] == '>' && input[data->i + 1] == '>')
		{
			data->i++;
			add_node(data, head, input, 4);
		}
		else if (data->cmd->quote == 0 && input[data->i] == '<' && input[data->i + 1] != '<')
			add_node(data, head, input, 5);
		
		else
			data->buff[data->j++] = input[data->i];

		if (input[data->i] != NULL)
			data->i++;
	}
	return (head);
}

void	*parsing(char *input_temp)
{
	t_data	data;
	t_list	*head;
	char	*input;

	input = ft_strtrim(input_temp, " ");
	initialize(input, &data, &head);
	parsing_all(input, &data, &head);
	if (*(data.buff))
		put_buff_into_cmdline(&data);
	free(input);
	free(data.buff);

	return (head);
}
