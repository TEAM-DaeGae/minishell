/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:46:24 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/06 21:13:23 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		do_redir(t_redir *r)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	printf("i'm do_redir! line 21\n");
	printf("fd: %d\n", fd);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], g_envp)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);

	printf("test test test\n");


	if (!exec_builtin(r->cmds)) // ??
		//(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

static int		do_dredir(t_redir *r)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], g_envp)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!exec_builtin(r->cmds) && // ??
		(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

static int		do_bredir(t_redir *r)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], g_envp)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (!exec_builtin(r->cmds) && // ??
		(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

void			cmd_redir(t_redir *r)
{
	int		i;
	int		ret;
	int		status;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		printf("i'm cmd_redir! line 95\n");
		printf("types:%d, REDIR:%d\n", r->types[r->argc-2], REDIR);
		if (r->types[r->argc - 2] == REDIR) // '>'
			ret = do_redir(r);
		else if (r->types[r->argc - 2] == DREDIR) // >>
			ret = do_dredir(r);
		else // '<'
			ret = do_bredir(r);
		exit(ret);
	}
	wait(&status);
	g_exit_status = status / 256;
	free(r->types);
	free_double_arr(r->argv);
	free_double_arr(r->cmds);
}
