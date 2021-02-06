/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/06 03:21:35 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_builtin(char **cmdline)
{
    char	*builtin;
    
    builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd"))
		ft_cd(cmdline, g_envp);
	else if (!ft_strcmp(builtin, "echo"))
		ft_echo(cmdline);
	else if (!ft_strcmp(builtin, "pwd"))
	 	ft_pwd();
	else if (!ft_strcmp(builtin, "env"))
		ft_env(g_envp);
	else if (!ft_strcmp(builtin, "export"))
		ft_export(cmdline);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(cmdline);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(cmdline);
	else
		exec_bin(cmdline);
	g_exit_status = 0;
	return (1);
}

void		exec_bin(char **cmdline)
{
	int		status;
	char	*path;
	pid_t	child;

	if (!(path = find_path(cmdline[0], g_envp)))
	{
		//free_double_arr(cmdline);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(path, cmdline, g_envp) == -1)
		{
			print_execute_err_1(cmdline[0], "command not found");
			exit(127);
		}
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, handle_child_signal);
	wait(&status);
	signal(SIGINT, handle_signal);
	free(path);
	//free_double_arr(cmdline);
	g_exit_status = status % 256;
}
