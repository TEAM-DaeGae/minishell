#include "minishell.h"

int		count_token(char *input)
{
	int		count_token;
	char	*p;

	count_token = 1;
	if (!(p = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (NULL);
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
	data->lst = *head;

	if (!(data->cmd = ft_calloc(1, sizeof(t_cmd))))
		return (ft_parsing_error( , MALLOC_ERROR)); // exit 코드 번호 정하기
	if (!(data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *)))) // 보류: char**이 calloc으로 가능?
		return (ft_parsing_error( , MALLOC_ERROR)); // 위와 동일
	data->cmd->flag = 0;
	data->cmd->quote = 0;

	if (!(data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (ft_parsing_error( , MALLOC_ERROR)); // 위와 동일
	data->i = 0;
	data->j = 0;
	data->k = 0;
}
