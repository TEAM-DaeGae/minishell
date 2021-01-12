/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:52:14 by daelee            #+#    #+#             */
/*   Updated: 2021/01/11 11:56:56 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(char **program)
{
	int		argc;

	argc = 0;
	while (program[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2 && ft_isdigit_str(program[1]))
	{
		exit(ft_atoi(program[1]));
	}
	else if (argc > 2 && ft_isdigit_str(program[1]))
		ft_putendl_fd("bash: exit: too many arguments", 1);
	else
	{
		ft_putstr_fd("bash: exit: numeric argument required", 1);
		exit(2);
	}
}