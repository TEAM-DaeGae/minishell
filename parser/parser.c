/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 21:59:36 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/07 22:35:00 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_parse_error;

int 	add_node(t_data *data, t_list *head, char *input, int symbol)
{
	data->cmd->flag = symbol;
	if (*(data->buff))
		put_buff_into_cmdline(data);
	if ((data->cmd->cmdlines)[0] == 0 && data->cmd->flag <= 1)
		return (ERROR);
	else
	{
		ft_lstadd_back(&head, ft_lstnew(data->cmd));
		data->cmd = ft_calloc(1, sizeof(t_cmd));
		data->cmd->cmdlines = ft_calloc(count_token(input) + 1, sizeof(char *));
		data->lstlast = ft_lstlast(head);
	}
	data->k = 0;
	return (SUCCESS);
}

void	put_buff_into_cmdline(t_data *data)
{
	if (*(data->buff) == 0)
		return;
	data->cmd->cmdlines[(data->k)] = ft_strdup(data->buff);
	data->cmd->cmdlines[(data->k) + 1] = NULL;
	(data->k)++;
	ft_bzero(data->buff, ft_strlen(data->buff) + 1);
	data->j = 0;
}

void	parse_all_char(char *input, t_data *data, t_list *head)
{
	if (data->cmd->quote == input[data->i])
	{
		data->cmd->quote = 0;
		if (input[data->i] == '\'')
			data->buff[data->j++] = input[data->i];
	}
	else if (data->cmd->quote == 0 && input[data->i] == '\"')
		data->cmd->quote = input[data->i];
	else if (data->cmd->quote == 0 && input[data->i] == '\'')
	{
		data->cmd->quote = input[data->i];
		data->buff[data->j++] = input[data->i];
	}
	else if (data->cmd->quote == 0 && input[data->i] == ' ')
		put_buff_into_cmdline(data);
	else if (data->cmd->quote == 0 && input[data->i] == ';')
		g_parse_error = add_node(data, head, input, 0);
	else if (data->cmd->quote == 0 && input[data->i] == '|')
		g_parse_error = add_node(data, head, input, 1);
	else
	{
		if (data->cmd->quote == 0 && ft_strchr("><", input[data->i]))
			data->cmd->has_redir = 1;
		else if (data->cmd->quote != '\'' && input[data->i] == '\\' && input[data->i + 1])
			data->i++;
		data->buff[data->j++] = input[data->i];
	}
}

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
	if (g_parse_error == 1)
		exec_process(head);
	return (NULL);
}
