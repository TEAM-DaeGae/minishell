/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 22:02:39 by daelee           ###   ########.fr       */
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

int exec_builtin(t_cmd *cmd)
{
	char *builtin;
	int ret;

	builtin = cmd->cmdline[0];
	ret = EXIT_FAILURE;
	if (!ft_strcmp(builtin, "cd"))
		ret = ft_cd(cmd, g_envp);
	else if (!ft_strcmp(builtin, "echo"))
		ret = ft_echo(cmd);
	else if (!ft_strcmp(builtin, "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(builtin, "env"))
		ret = ft_env(g_envp);
	else if (!ft_strcmp(builtin, "export"))
		ret = ft_export(cmd);
	else if (!ft_strcmp(builtin, "unset"))
		ret = ft_unset(cmd);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(cmd);
	return (ret / 256);
}

// int exec_child_proc(t_cmd *cmd, t_cmd *next_cmd)
// {
// 	int ret;
// 	char *path;

// 	ret = EXIT_SUCCESS;
// 	path = find_path(cmd->cmdline[0], g_envp);
// 	if (cmd->flag == 1)
// 	{
// 		dup2(next_cmd->fds[1], STDOUT);
// 		close(next_cmd->fds[1]);
// 	}
// 	if (cmd->fds[0] != 0)
// 	{
// 		dup2(cmd->fds[0], STDIN);
// 		close(cmd->fds[0]);
// 	}
// 	if (check_builtin(cmd->cmdline) == TRUE)
// 		exec_builtin(cmd->cmdline);
// 	else (ret = execve(path, cmd->cmdline, g_envp));
// 	if (ret == -1)
// 		print_execute_err_1(cmd->cmdline[0], "command not found");
// 	return (ret);
// }

int exec_cmds(t_list *cur_proc, t_cmd *cmd)
{
	pid_t pid;
	int ret;
	int status;
	t_cmd *next_cmd;
	char *path;

	ret = EXIT_SUCCESS;
	path = find_path(cmd->cmdline[0], g_envp);
	next_cmd = cur_proc->content;
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		//printf("cmd test : %s\n", next_cmd->cmdline[0]);
		pipe(next_cmd->fds);
	}
	pid = fork();
	if (pid == 0)
	{
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
			ret = exec_builtin(cmd);
		else
			(ret = execve(path, cmd->cmdline, g_envp));
		if (ret == -1)
			print_execute_err_1(cmd->cmdline[0], "command not found");
	}
		//ret = exec_child_proc(cmd, next_cmd);
	printf("fds 0 : %d\n",cmd->fds[0]);
	printf("fds 1 : %d\n", cmd->fds[1]);
	waitpid(pid, &status, 0);
	if (cmd->flag == 1)
		close(next_cmd->fds[1]);
	if (cmd->fds[0] != 0) // 앞에 파이프가 열려있는 상태
		close(cmd->fds[0]);
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
			if ((check_builtin(cmd->cmdline) == TRUE) && cmd->flag == 0)
				exec_builtin(cmd);
			else
				exec_cmds(cur_proc, cmd);
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}
