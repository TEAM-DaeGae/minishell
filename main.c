/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 14:09:21 by daelee           ###   ########.fr       */
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
    //free(input);
	}
	return (0);
}