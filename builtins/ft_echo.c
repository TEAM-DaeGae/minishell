/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 14:10:17 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_echo(char **cmdline)
{
	int		i;
	int		option;
	int 	ret;

	i = 0;
	option = 0;
	ret = EXIT_SUCCESS;
	while (cmdline[++i])
	{
		while (cmdline[i] && (option + 1) == i &&
		!ft_strcmp(cmdline[i], "-n"))
		{
			if (cmdline[i + 1] == NULL)
				return (ret);
			option++;
			i++;
		}
		ft_putstr_fd(cmdline[i], STDIN);
		if (cmdline[i + 1] != NULL)
			ft_putstr_fd(" ", STDIN);
	}
	if (option == 0)
		ft_putstr_fd("\n", STDIN);
	return (ret);
}