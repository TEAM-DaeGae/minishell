#include <stdio.h>

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_cmd
{
	char	**cmdline; 
	int		flag;
	char	quote;
}				t_cmd;

typedef struct	s_data
{
	char	*buff;

	int		i;
	int		j;
	int		k;

	t_cmd	*cmd;
	t_list	*lst;
}				t_data;

int		put_buff_into_cmdline(t_data *data)
{
	data->cmdline[data->k] = ft_strdup(data->buff);
	(data->k)++;

	ft_bzero(data->buff, ft_strlen(data->buff) + 1);

	data->j= 0;
}

int		cmd_count(char *input)
{
	int		cmd_count;
	char	*p;

	cmd_count = 1;
	if (!(p = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (NULL);
	ft_strcpy(p, input);
	if (ft_strtok(p, ' ') != NULL)
	{
		while (ft_strtok(NULL, ' ') != NULL)
			cmd_count++;
	}
	return (cmd_count);
}

void	initialize(char *input, t_list **head, t_data *data)
{
	if (!(data->cmd->cmdline = malloc(sizeof(char *) * (cmd_count(input) + 1))))
		return (NULL);
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	
	if (!(data->buff = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (NULL);
	
	data->i = 0;
	data->j = 0;
	data->k = 0;

	if (!(data->cmd = ft_calloc(1, sizeof(t_cmd))))
		return (NULL);
	
	*head = ft_lstnew(NULL);
	data->lst = *head;
}

void	parsing(char *input)
{
	t_list	*head;
	t_data	data;	

	initialize(input, &head, &data);

	while (input[data.i])
	{
		if (data.cmd->quote != '\'' && input[data.i] == '\'')
			until_close_quote();
		else if (data.cmd->quote != '\"' && input[data.i] == '\"')
			until_close_quote();
		else if (data.cmd->quote == 0 && input[data.i] == ' ')
			put_buff_into_cmdline(&data);
		else if (data.cmd->quote == 0 && (input[data.i] == ';' || input[data.i] == NULL))
			add_content(  , 1);
		else if (data.cmd->quote == 0 && input[data.i] == '|')
			add_content(  , 2);
		else if (data.cmd->quote == 0 && input[data.i] == '>' && input[i + 1] != '>')
			add_content(   , 3);
		else if (data.cmd->quote == 0 && input[data.i] == '>' && input[i + 1] == '>')
			add_content(   , 4);
		else if (data.cmd->quote == 0 && input[data.i] == '<' && input[i + 1] != '<')
			add_content(   , 5);
		else
			data.buff[(data.j)++] = input[data.i];
		i++;
	}
}

int		main(int argc, char **argv, char **envp)
{
    char    input[];

	input = "ls -al; echo 'Hello'";

	parsing(input);

	return (0);
}
