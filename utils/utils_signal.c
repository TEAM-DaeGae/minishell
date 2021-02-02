/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:29:46 by daelee            #+#    #+#             */
/*   Updated: 2021/02/03 02:03:22 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_signal(void)
{
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void	handle_child_signal(int signo)
{
	if (signo == SIGINT)
		write(STDERR, "\n", 1);
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(STDERR, "\b\b", 2);
		write(STDERR, "  \n", 3);
		show_prompt();
	}
	else if (signo == SIGQUIT)
	{
		signo = wait(&signo);
		write(STDERR, "\b\b  \b\b", 6);
		if (signo != -1)
			write(STDERR, "^\\Quit: 3\n", 10);
	}
}
