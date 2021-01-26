/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/26 18:21:16 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
char	**g_envp = NULL;

void	show_daegae(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii_art", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_putstr_fd("\033[36m", STDIN_FILENO);
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

	ft_putstr_fd(" \033[1;96m", STDIN_FILENO);
	ft_putstr_fd(getcwd(curpath, MAXSIZE), STDIN_FILENO);
	ft_putstr_fd("\033[1;93m $\033[0m ", STDIN_FILENO);
}

int		main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*data_list;

	char    **cmdline = malloc(sizeof(char *) * 3);
     cmdline[0] = ft_strdup("cd");
     cmdline[1] = ft_strdup("sds");
     cmdline[2] = ft_strdup(0);
	 
	(void)argc;
	(void)argv;
	g_envp = copy_envp(envp);
	set_signal();
	show_daegae();
	while (1)
	{
		show_prompt();
		if (!get_next_line(0, &input) && !ft_strlen(input))
		{
			free(input);
			ft_putstr_fd("  \b\b", STDIN_FILENO);
			ft_putstr_fd("exit\n", STDIN_FILENO);
			exit(EXIT_SUCCESS);
		}
		exec_builtin(cmdline);
		// else if (parsing(input))
		// {
		
		// }
    free(input);
	}
	return (0);
}