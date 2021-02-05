/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:52:14 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 16:04:10 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		ft_exit(t_cmd *cmd)
{
	int		argc;

	argc = 0;
	// printf("flag : %d\n", cmd->flag);
	// printf("preflag : %d\n", cmd->preflag);
	// printf("fds[0] : %d\n", cmd->fds[0]);
	// printf("fds[1] : %d\n", cmd->fds[1]);
	if (cmd->preflag == 1)
		return ;
	while (cmd->cmdline[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2 && ft_isdigit_str(cmd->cmdline[1]))
	{
		exit(ft_atoi(cmd->cmdline[1]));
	}
	else if (argc > 2 && ft_isdigit_str(cmd->cmdline[1]))
		ft_putendl_fd("bash: exit: too many arguments", STDIN);
	else
	{
		ft_putstr_fd("bash: exit: numeric argument required", STDIN);
		exit(255);
	}
}