/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/11 10:08:29 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void               show_daegae(void)
{
    int		fd;
	char	*line;

	fd = open("ascii_art", O_RDONLY);
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

void               show_prompt()
{
    static char    *curpath;
    ft_putstr_fd(" \033[1;96m", 1);
    ft_putstr_fd(getcwd(curpath, MAXSIZE), 1);
    ft_putstr_fd("\033[1;93m $\033[0m ", 1);
}

int		    main(int argc, char **argv, char **envp)
{
    char    *input;
    t_list  *data_list;
    char    **program = malloc(sizeof(char *) * 5);
    program[0] = ft_strdup("exit");
    program[1] = ft_strdup("hello");
    program[2] = ft_strdup("world");
    program[3] = ft_strdup("daelee");
    program[4] = ft_strdup(0);
    
    g_envp = envp;
    show_daegae();
    while (1)
    {
        show_prompt();
        get_next_line(0, &input); //-1인 경우 에러메세지?
        //parsing(&data, input); //free(data, input)
        //printf("%s\n", input);
        //exec_cmds(program);
        exec_builtin(program);
        //free(input);
    }
	return (0);
}