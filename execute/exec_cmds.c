/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 01:13:00 by daelee           ###   ########.fr       */
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
	return (ret);
}

int exec_execve(t_cmd *cmd)
{
	int status;
	char *path;
	pid_t pid;
	int ret;

	ret = EXIT_SUCCESS;
	if (!(path = find_path(cmd->cmdline[0], g_envp)))
	{
		//free_double_arr(cmdline);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		if ((ret = execve(path, cmd->cmdline, g_envp)) == -1)
			print_execute_err_1(cmd->cmdline[0], "command not found");
	}
	signal(SIGINT, handle_signal);
	waitpid(pid, &status, 0);
	free(path);
	//free_double_arr(cmdline);
	return (ret);
}

int exec_pipe(t_cmd *cmd, t_list *next_cmd)
{
	pid_t pid;
	int ret;
	int status;

	ret = EXIT_SUCCESS;
	pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
		close(cmd->fds[1]);
		dup2(cmd->fds[0], STDIN);
		close(cmd->fds[0]);
	}
	// printf("fds 0 : %d\n", cmd->fds[0]);
	// printf("fds 1 : %d\n", cmd->fds[1]);
	close(cmd->fds[0]);
	dup2(cmd->fds[1], STDOUT);
	close(cmd->fds[1]);
	waitpid(pid, &status, 0);
	
	// if (cmd->preflag == 1)
	//  	close(cmd->fds[1]);
	// if (cmd->fds[0] != 0) // 앞에 파이프가 열려있는 상태
	// 	close(cmd->fds[0]);
	return (ret);
}

int exec_cmds(t_list *cur_proc, t_cmd *cmd)
{
	int ret;
	t_cmd *next_cmd;

	ret = EXIT_FAILURE;
	next_cmd = cur_proc->content; //NULL이면 초기화 불가능
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		if (next_cmd->flag == 0)
			cmd->preflag = 1;
		exec_pipe(cmd, next_cmd);
	}
	if (check_builtin(cmd->cmdline) == TRUE)
		exec_builtin(cmd);
	else
		exec_execve(cmd);
	return (ret);
}

void exec_process(t_list *head) // 인자는 연결리스트의 헤드포인터
{
	t_list *cur_proc;
	t_cmd *cmd;
	int ret;

	ret = EXIT_SUCCESS;
	cur_proc = head->next;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content; // (t_cmd *)형태로 자료형변환을 위해 옮겨담음.
		if (cmd->cmdline[0])
		{
			// if ((check_builtin(cmd->cmdline) == TRUE) && cmd->flag == 0)
			// 	exec_builtin(cmd);
			// else
			ret = exec_cmds(cur_proc, cmd);
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}
