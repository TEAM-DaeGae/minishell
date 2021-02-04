/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 14:21:08 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtin(char **cmdline)
{
	char *builtin;

	builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo") || !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env") || !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (TRUE);
	return (FALSE);
}

int exec_builtin(char **cmdline)
{
	char *builtin;
	int ret;

	builtin = cmdline[0];
	ret = EXIT_FAILURE;
	if (!ft_strcmp(builtin, "cd"))
		ret = ft_cd(cmdline, g_envp);
	else if (!ft_strcmp(builtin, "echo"))
		ret = ft_echo(cmdline);
	else if (!ft_strcmp(builtin, "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(builtin, "env"))
		ret = ft_env(g_envp);
	else if (!ft_strcmp(builtin, "export"))
		ret = ft_export(cmdline);
	else if (!ft_strcmp(builtin, "unset"))
		ret = ft_unset(cmdline);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(cmdline);
	return (ret);
}

int exec_child_proc(t_cmd *cmd, t_cmd *next_cmd)
{
	int ret;
	char *path;

	ret = EXIT_SUCCESS;
	path = find_path(cmd->cmdline[0], g_envp);
	if (cmd->flag == 1)
	{
		dup2(next_cmd->fds[1], STDOUT);
		close(next_cmd->fds[1]);
	}
	if (cmd->fds[0] != 0)
	{
		dup2(cmd->fds[0], STDIN);
		close(cmd->fds[0]);
	}
	if (check_builtin(cmd->cmdline) == TRUE)
	{
		if ((exec_builtin(cmd->cmdline)) == 1)
			close(cmd->fds[0]);
		}
	else (ret = execve(path, cmd->cmdline, g_envp));
	if (ret == -1)
		print_execute_err_1(cmd->cmdline[0], "command not found");
	return (ret);
}

int exec_cmds(t_list *cur_proc, t_cmd *cmd)
{
	pid_t pid;
	int ret;
	int status;
	t_cmd *next_cmd;

	ret = EXIT_FAILURE;
	next_cmd = cur_proc->content;
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		pipe(next_cmd->fds);
	}
	pid = fork();
	if (pid == 0)
		ret = exec_child_proc(cmd, next_cmd);
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

void exec_proc(t_list *head) // 인자는 연결리스트의 헤드포인터
{
	t_list *cur_proc;
	t_cmd *cmd;

	cur_proc = head->next;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content; // (t_cmd *)형태로 자료형변환을 위해 옮겨담음.
		if (cmd->cmdline[0])
		{
			if (check_builtin(cmd->cmdline) == TRUE)
				exec_builtin(cmd->cmdline);
			else
				exec_cmds(cur_proc, cmd);
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}
