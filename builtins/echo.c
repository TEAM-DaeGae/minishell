/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/01/08 11:03:31 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **argv)
{
	int		idx;
	int		endl;

	idx = 0;
	endl = 0;
	while (argv[++idx])
	{
		while (argv[idx] && (endl + 1) == idx &&
		!ft_strncmp(argv[idx], "-n", ft_strlen(argv[idx])))
		{
			if (argv[idx + 1] == NULL)
				return ;
			endl++;
			idx++;
		}
		ft_putstr_fd(argv[idx], 1);
		if (argv[idx + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!endl)
		ft_putstr_fd("\n", 1);
}