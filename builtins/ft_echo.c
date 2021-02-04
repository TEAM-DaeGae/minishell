/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 00:22:54 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		ft_echo(t_cmd *cmd)
{
	int		i;
	int		option;
	int 	ret;

	i = 0;
	option = 0;
	ret = EXIT_SUCCESS;
	while (cmd->cmdline[++i])
	{
		while (cmd->cmdline[i] && (option + 1) == i &&
			   !ft_strcmp(cmd->cmdline[i], "-n"))
		{
			if (cmd->cmdline[i + 1] == NULL)
				return (ret);
			option++;
			i++;
		}
		ft_putstr_fd(cmd->cmdline[i], STDIN);
		if (cmd->cmdline[i + 1] != NULL)
			ft_putstr_fd(" ", STDIN);
	}
	if (option == 0)
		ft_putstr_fd("\n", STDIN);
	return (ret);
}