/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/02 20:58:32 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtin(char **cmdline)
{
	char *builtin;

	builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo") 
	|| !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env") 
	|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export") 
	|| !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}

int 		exec_builtin(char **cmdline)
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
	return (1);
}

int exec_cmds(t_list *cur_proc, t_cmd *cmd)
{
	pid_t pid;
	int ret;
	int status;
	int fds[2];
	char *path;

	ret = EXIT_FAILURE;
	path = find_path(cmd->cmdline[0], g_envp);
	if (cmd->flag == 1)
	{
		if (pipe(fds))
			return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if (cmd->flag == 1 && dup2(fds[0], STDIN) < 0)
			return (EXIT_FAILURE);
		if ((ret = execve(path, cmd->cmdline, g_envp)) < 0)
			print_execute_err_1(cmd->cmdline[0], "command not found");
		close(fds[0]);
		close(fds[1]);
	}
	waitpid(pid, &status, 0);
	close(fds[0]);
	dup2(fds[1], STDOUT);
	cur_proc = cur_proc->next;
	close(fds[1]);
	// if (WIFEXITED(status))
	// 	ret = WEXITSTATUS(status);
	return (ret);
}

// void		exec_bin(char **cmdline)
// {
// 	int		status;
// 	char	*path;
// 	pid_t	child;

// 	if (!(path = find_path(cmdline[0], g_envp)))
// 	{
// 		//free_double_arr(cmdline);
// 		return ;
// 	}
// 	child = fork();
// 	if (child == 0)
// 	{
// 		if (execve(path, cmdline, g_envp) == -1)
// 		{
// 			print_execute_err_1(cmdline[0], "command not found");
// 			exit(127);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	signal(SIGINT, handle_child_signal);
// 	wait(&status);
// 	signal(SIGINT, handle_signal);
// 	free(path);
// 	//free_double_arr(cmdline);
// 	g_exit_status = status % 256;
// }
