//include "minishell_gaekim.h"
#include "minishell.h"

static void	clear_ptr1(t_data *ptr1)
{
	if (ptr1->buff)
	{
		free(ptr1->buff);
		ptr1->buff = NULL;
	}
	if (ptr1->cmd->quote == 0)
	{
		if (ptr1->cmd)
		{
			if (ptr1->cmd->cmdline)
			{
				free_double_str(ptr1->cmd->cmdline);
				ptr1->cmd->cmdline = NULL;
			}
			free(ptr1->cmd);
			ptr1->cmd = NULL;
		}
	}
}

void	free_double_str(char **ptr)
{
	int idx;

	idx = 0;
	if (ptr)
	{
		while (ptr[idx])
		{
			free(ptr[idx]);
			ptr[idx] = NULL;
			idx++;
		}
		free(ptr);
		ptr = NULL;
	}
}

void	free_cmdline(void *content)
{
	t_cmd	*command;

	command = (t_cmd *)content;
	if (command)
	{
		if (command->cmdline)
		{
			free_double_str(command->cmdline);
			command->cmdline = NULL;
		}
		free(command);
	}
}

void    *parse_error(t_data *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
		clear_ptr1(ptr1);
	if (ptr2)
	{
		ft_lstclear(&(ptr2->next), free_cmdline);
		free(ptr2);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(comment, STDERR_FILENO);
	if (!ft_strncmp(comment, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR)))
		g_exit_status = 2 * 256;
	else
		g_exit_status = 1 * 256;
	
    g_parse_error = 0; // return NULL 대신 error 플래그로 추가함.

	return (NULL);
}