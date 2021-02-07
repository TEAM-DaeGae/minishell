/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 19:02:02 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/08 01:39:13 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(char *command, t_redir *re)
{
	int num;

	num = 0;
	while (*command)
	{
		if (ft_strchr("><", *command))
			num++;
		command++;
	}
	re->argc = num + 1;
	re->argv = (char **)malloc(sizeof(char *) * (re->argc + 1));
	re->types = (char *)malloc(sizeof(char) * (re->argc + 1));
	re->cmds = NULL;
}

int		parse_redir_final(t_redir *r, int j)
{
	if (has_redir_syntax_error(r->argv[j]))
		return (-1);
	r->types[j] = 0;
	j++;
	r->argv[j] = 0;
	r->argc = j;
	return (1);
}

int		parse_redir(char *command, t_redir *r)
{
	int		i;
	int		j;
	int		start;

	i = -1;
	j = 0;
	start = 0;
	while (command[++i])
	{
		if (ft_strchr("><", command[i]))
		{
			if (j > 0 && ((r->types[0] == BREDIR && command[i] == '>') ||
				(r->types[0] != BREDIR && command[i] == '<')))
				return (0);
			r->argv[j] = substr_and_trim(command, start, i - start, " ");
			if (j == 0)
				r->cmds = ft_split(r->argv[j], ' ');
			r->types[j] = find_redir_type(command, i);
			(r->types[j] == DREDIR) ? i++ : 0;
			j++;
			start = i + 1;
		}
	}
	r->argv[j] = substr_and_trim(command, start, i - start, " ");
	return (parse_redir_final(r, j));
}

void	open_unnecessary_files(t_redir *r)
{
	int		i;
	int		fd;

	i = 1;
	while (i < r->argc - 1)
	{
		if (i > 1)
			close(fd);
		if (r->types[i - 1] == REDIR)
			fd = open(r->argv[i], O_WRONLY | O_CREAT | O_TRUNC, 0744);
		else if (r->types[i - 1] == DREDIR)
			fd = open(r->argv[i], O_WRONLY | O_CREAT | O_APPEND, 0744);
		else
			fd = open(r->argv[i], O_RDONLY, 0644);
		i++;
	}
	close(fd);
}

void	exec_redir(t_cmd *cmd, char **cmdline)
{
	int		ret;
	t_redir	r;
	char	*line;

	line = change_from_double_to_single_cmdline(cmdline);
	line = remove_single_quotes(line);
	init_redir(line, &r);
	if ((ret = parse_redir(line, &r)) <= 0)
	{
		if (ret < 0)
			ft_putendl_fd("syntax error near unexpected token `newline'", 1);
		return ;
	}
	open_unnecessary_files(&r);
	cmd_redir(cmd, &r);
}
