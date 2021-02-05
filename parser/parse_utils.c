#include "minishell.h"

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
	data->cmd->has_redir = 0; // 리다이렉션 플래그 초기화 추가
	if (!(data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return ((void *)parse_error(data, NULL, MALLOC_ERROR));
	data->i = -1;
	data->j = 0;
	data->k = 0;
	return (NULL);
}