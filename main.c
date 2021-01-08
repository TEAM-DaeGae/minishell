/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/08 19:04:58 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void               show_prompt()
{
    // int		fd;
	// char	*line;

	// fd = open("ascii_art", O_RDONLY);
	// while (get_next_line(fd, &line))
	// {
	// 	printf("%s\n", line);
	// 	free(line);
	// }
    // printf("%s\n", line);
	// close(fd);
	// free(line);
    static char    *curpath;
    ft_putstr_fd(" \033[1;96m", 1);
    ft_putstr_fd(getcwd(curpath, MAXSIZE), 1);
    ft_putstr_fd("\033[1;93m $\033[0m ", 1);
}

int		    main(int argc, char **argv, char **envp)
{
    char    *input;
    t_list  *data_list;
    int     ret;
    char    **program = malloc(sizeof(char *) * 2);
    program[0] = ft_strdup("pwd");
    program[1] = ft_strdup(0);
    
    g_envp = envp;
    ret = 1;
    while (ret)
    {
        show_prompt();
        ret = get_next_line(0, &input); //-1인 경우 에러메세지?
        //parsing(&data, input); //free(data, input)
        //printf("%s\n", input);
        //exec_cmds(program);
        exec_builtin(program);
        //free(input);
    }
	return (0);
}