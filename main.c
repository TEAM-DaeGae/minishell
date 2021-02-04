/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 20:16:16 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
char	**g_envp = NULL;
t_list 	*g_proc_list;   // parse_proc에서 복사함
int 	g_parse_error = 1; // 1이면 정상, 0이면 에러 발생

void	show_daegae(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii_art", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_putstr_fd("\033[36m", STDIN);
		ft_putendl_fd(line, STDOUT);
		free(line);
	}
	ft_putendl_fd(line, STDOUT);
	close(fd);
	free(line);
	ft_putendl_fd("\033[0m", 1);
}

void	show_prompt(void)
{
	static char	*curpath;

	ft_putstr_fd(" \033[1;96m", STDIN);
	ft_putstr_fd(getcwd(curpath, MAXSIZE), STDIN);
	ft_putstr_fd("\033[1;93m $\033[0m ", STDIN);
}

int 		get_command_line(char **input)
{
	int 	ret;
	char 	*input2;
	char 	*tmp;

	*input = ft_strdup("");
	while (TRUE)
	{
		ret = get_next_line(STDIN, &input2);
		tmp = ft_strjoin(*input, input2);
		free(input2);
		free(*input);
		*input = tmp;
		if (ret == 0)
		{
			ft_putstr_fd("  \b\b", STDOUT);
			if (ft_strlen(*input) != 0)
				continue;
			ft_putstr_fd("exit\n", STDOUT);
		}
		break;
	}
	return (ret);
}

int			main(int argc, char **argv, char **envp)
{
	char	*input;
	int 	ret;

	(void)argv;
	g_envp = copy_envp(envp);
	set_signal();
	show_daegae();
	ret = argc;
	while (ret)
	{
		show_prompt();
		ret = get_command_line(&input);
 		if (!check_white_space(input))
 			parse(input);
		free(input);
	}
	return (g_exit_status & 255);
}
