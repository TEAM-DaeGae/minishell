/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:29:46 by daelee            #+#    #+#             */
/*   Updated: 2021/01/13 18:48:14 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern 	char **g_envp;
extern	int g_signal;
extern	int g_exit_status;

void    set_signal(void)
{
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
}

void	handle_signal(int signo)
{
	(void)signo;
	g_exit_status = 256;
	write(STDERR_FILENO, "\b\b", 2);
	if (signo != SIGTERM)
		write(STDERR_FILENO, "  \n", 3);
	if (g_signal)
		show_prompt();
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