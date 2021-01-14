/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 19:06:00 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
int		g_signal = 1;
char	**g_envp = NULL;

void	show_daegae(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii_art", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_putstr_fd("\033[36m", 1);
		ft_putendl_fd(line, STDOUT_FILENO);
		free(line);
	}
	ft_putendl_fd(line, STDOUT_FILENO);
	close(fd);
	free(line);
	ft_putendl_fd("\033[0m", 1);
}

void	show_prompt(void)
{
	static char	*curpath;

	ft_putstr_fd(" \033[1;96m", 1);
	ft_putstr_fd(getcwd(curpath, MAXSIZE), 1);
	ft_putstr_fd("\033[1;93m $\033[0m ", 1);
}

int		main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*data_list;

	(void)argc;
	(void)argv;
	g_envp = copy_envp(envp);
	set_signal();
	show_daegae();
	while (1)
	{
		show_prompt();
		if (!get_next_line(0, &input))
		{
		
		}
		else if (parsing(input))
		{
		
		}
        //parsing(&data, input); //free(data, input)
        //exec_cmds(program);
		exec_builtin(program);
        //free(input);
	}
	return (0);
}

/*
int		main(int argc, char **argv, char **envp)
{
    char    input[];
	input = "ls -al; echo 'Hello'";

	t_list	*head; // command 정보를 담은 연결리스트의 헤드포인터
	t_list	*curr;

	(void)argc; // unused value 오류 탈피
	(void)argv;

	head = parsing(input); // parsing 함수가 연결리스트 헤드포인터 반환
	curr = head; // 포인터 curr를 연결리스트의 헤드포인터(노드1)로 초기화
	while (curr != NULL)
	{
		minishell_execute(curr->content);
		curr = curr->next;
	}
	return (0);
}
*/
