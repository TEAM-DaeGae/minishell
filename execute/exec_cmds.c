/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/03 02:20:11 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtin(char **cmdline)
{
	char *builtin;

	builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo") || !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env") || !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}

int exec_builtin(char **cmdline)
{
	char *builtin;

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
	return (1);
}

int exec_cmds(t_list *cur_proc, t_cmd *cmd)
{
	pid_t pid;
	int ret;
	int status;
	char *path;
	t_cmd *next_cmd;

	ret = EXIT_FAILURE;
	path = find_path(cmd->cmdline[0], g_envp);
	next_cmd = cur_proc->content;
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		if (pipe(next_cmd->fds) == -1)
			return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if (cmd->flag == 1)
		{
			dup2(next_cmd->fds[1], STDOUT);
			close(next_cmd->fds[1]);
			close(next_cmd->fds[0]);
		}
		if (cmd->fds[0] != 0)
		{
			dup2(cmd->fds[0], STDIN);
			close(cmd->fds[0]);
			close(cmd->fds[1]);
		}
		if ((ret = execve(path, cmd->cmdline, g_envp)) == -1)
			print_execute_err_1(cmd->cmdline[0], "command not found");
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd->flag == 1)
			close(next_cmd->fds[1]);
		if (cmd->fds[0] != 0) // 앞에 파이프가 열려있는 상태
			close(cmd->fds[0]);
	}
	return (ret);
}