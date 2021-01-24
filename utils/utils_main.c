/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:29:46 by daelee            #+#    #+#             */
/*   Updated: 2021/01/24 10:01:14 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern 	char **g_envp;
extern	int g_exit_status;

void    set_signal(void)
{
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
}

void	handle_child_signal(int signo)
{
	if (signo == SIGINT)
		write(STDERR_FILENO, "\n", 1);
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(STDERR_FILENO, "\b\b", 2);
		write(STDERR_FILENO, "  \n", 3);
		show_prompt();
	}
	else if (signo == SIGQUIT)
	{
		signo = wait(&signo);
		write(STDERR_FILENO, "\b\b  \b\b", 6);
		if (signo != -1)
			write(STDERR_FILENO, "^\\Quit: 3\n", 10);
	}
}

char	**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}