/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/07 23:03:55 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_child_process(t_cmd *cmd, t_cmd *next_cmd)
{
	int ret;
	char *path;

	ret = EXIT_SUCCESS;
	path = find_path(cmd->cmdlines[0], g_envp);
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
	if (check_builtin(cmd->cmdlines) == TRUE)
		exec_builtin(cmd, cmd->cmdlines);
	else
		(ret = execve(path, cmd->cmdlines, g_envp));
	if (ret == -1)
		print_execute_err_1(cmd->cmdlines[0], "command not found");
	exit(ret);
}

int exec_pipe(t_list *cur_proc, t_cmd *cmd)
{
	pid_t pid;
	int ret;
	int status;
	t_cmd *next_cmd;
	char *path;

	ret = EXIT_SUCCESS;
	path = find_path(cmd->cmdlines[0], g_envp);
	next_cmd = cur_proc->content;
	if (cmd->flag == 1)
	{
		next_cmd = cur_proc->next->content;
		next_cmd->preflag = 1;
		pipe(next_cmd->fds);
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, next_cmd);
	waitpid(pid, &status, 0);
	if (cmd->flag == 1)
		close(next_cmd->fds[1]);
	if (cmd->fds[0] != 0)
		close(cmd->fds[0]);
	return (ret);
}

void exec_builtin(t_cmd *cmd, char **cmdline)
{
	char *builtin;

	builtin = cmd->cmdlines[0];
	if (!ft_strcmp(builtin, "cd"))
		ft_cd(cmdline, g_envp);
	else if (!ft_strcmp(builtin, "echo"))
		ft_echo(cmdline, g_envp);
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(builtin, "env"))
		ft_env(g_envp);
	else if (!ft_strcmp(builtin, "export"))
		ft_export(cmd, cmdline);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(cmd, cmdline);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(cmd, cmdline);
}

void exec_process(t_list *head)
{
	t_list *cur_proc;
	t_cmd *cmd;

	cur_proc = head->next;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content;
		if (cmd->cmdlines[0])
		{
			if ((check_builtin(cmd->cmdlines) == TRUE) && cmd->flag == 0)
				exec_builtin(cmd, cmd->cmdlines);
			else
				exec_pipe(cur_proc, cmd);
			// if (cmd->has_redir == 1 && cmd->flag == 0)
			// 	exec_redir(cmd, cmd->cmdlines);
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}
