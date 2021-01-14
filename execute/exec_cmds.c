/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 14:39:18 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern 	char **g_envp;
extern 	int  g_exit_status;

int				exec_builtin(char **cmdline)
{
    char        *builtin;
    
    builtin = cmdline[0];
	if (!ft_strncmp(builtin, "cd", ft_strlen(builtin)))
		ft_cd(cmdline, g_envp);
	else if (!ft_strncmp(builtin, "echo", ft_strlen(builtin)))
		ft_echo(cmdline);
	else if (!ft_strncmp(builtin, "pwd", ft_strlen(builtin)))
	 	ft_pwd();
	else if (!ft_strncmp(builtin, "env", ft_strlen(builtin)))
		ft_env(g_envp);
	else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
		ft_export(cmdline);
	else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)))
		ft_unset(cmdline);
	else if (!ft_strncmp(builtin, "exit", ft_strlen(builtin)))
		ft_exit(cmdline);
	else
		return (0);
	free_double_arr(cmdline);
	g_exit_status = 0;
	return (1);
}

void			exec_bin(char **cmdline)
{
	int		status;
	char	*path;
	pid_t	child;

	if (!(path = find_path(cmdline[0], g_envp)))
	{
		free_double_arr(cmdline);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(path, cmdline, g_envp) == -1)
			exit(ft_puterror_fd(cmdline[0], ": command not found", 2));
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, handle_child_signal);
	wait(&status);
	signal(SIGINT, handle_signal);
	free(path);
	free_double_arr(cmdline);
	g_exit_status = status / 256;
}

void			exec_cmds(char **cmdline)
{
    if (exec_builtin(cmdline) == 0)
		exec_bin(cmdline);
}