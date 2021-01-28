/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:52:14 by daelee            #+#    #+#             */
/*   Updated: 2021/01/29 02:28:30 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(char **cmdline)
{
	int		argc;

	argc = 0;
	while (cmdline[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2 && ft_isdigit_str(cmdline[1]))
	{
		exit(ft_atoi(cmdline[1]));
	}
	else if (argc > 2 && ft_isdigit_str(cmdline[1]))
		ft_putendl_fd("bash: exit: too many arguments", STDIN);
	else
	{
		ft_putstr_fd("bash: exit: numeric argument required", STDIN);
		exit(255);
	}
}