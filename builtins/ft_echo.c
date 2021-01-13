/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/01/13 19:28:42 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(char **program)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	while (program[++i])
	{
		while (program[i] && (option + 1) == i &&
		!ft_strncmp(program[i], "-n", ft_strlen(program[i])))
		{
			if (program[i + 1] == NULL)
				return ;
			option++;
			i++;
		}
		ft_putstr_fd(program[i], 1);
		if (program[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}