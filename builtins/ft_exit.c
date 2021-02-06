/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:52:14 by daelee            #+#    #+#             */
/*   Updated: 2021/02/06 21:28:12 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_exit_errcode(void)
{
	ft_putstr_fd("exit\n", STDERR);
	exit(g_exit_status);
}

void 		ft_exit(t_cmd *cmd)
{
	int		argc;

	argc = 0;
	if (cmd->preflag == 1)
		return ;
	while (cmd->cmdline[argc] != NULL)
		argc++;
	if (argc == 1)
		ft_exit_errcode();
	else if (argc == 2 && ft_isdigit_str(cmd->cmdline[1]))
		g_exit_status = ft_atoi(cmd->cmdline[1]);
	else if (argc > 2 && ft_isdigit_str(cmd->cmdline[1]))
	{
		ft_putstr_fd("exit\n", STDERR);
		print_execute_err_1("exit", "too many arguments");
		g_exit_status = 1;
		return ;
	}
	else
	{
		print_execute_err_2("exit", cmd->cmdline[1], "numeric argument required");
		g_exit_status = 255;
		exit(g_exit_status & 255);
	}
	ft_exit_errcode();
}