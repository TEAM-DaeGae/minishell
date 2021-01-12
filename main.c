/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:46:05 by daelee            #+#    #+#             */
/*   Updated: 2021/01/12 22:55:16 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
char	**g_envp = NULL;

char	**ft_first_envv(char **envv)
{
	char	**new;
	int		i;

	i = 0;
	while (envv[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (envv[++i])
		new[i] = ft_strdup(envv[i]);
	new[i] = NULL;
	return (new);
}

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
    char    **program = malloc(sizeof(char *) * 3);
    program[0] = ft_strdup("unset");
    program[1] = ft_strdup(0);
    program[2] = ft_strdup(0);
    
    g_envp = ft_first_envv(envp);
    show_daegae();
    while (1)
    {
        show_prompt();
        get_next_line(0, &input); //-1인 경우 에러메세지?
        //parsing(&data, input); //free(data, input)
        //exec_cmds(program);
        exec_builtin(program);
        //free(input);
    }
	return (0);
}