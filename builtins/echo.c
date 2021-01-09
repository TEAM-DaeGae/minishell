/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/01/09 11:02:41 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **program)
{
	int		i;
	int		endl;

	i = 0;
	endl = 0;
	while (program[++i])
	{
		while (program[i] && (endl + 1) == i &&
		!ft_strncmp(program[i], "-n", ft_strlen(program[i]))) //-n이면 endl++, i++
		{
			if (program[i + 1] == NULL)
				return ;
			endl++;
			i++;
		}
		ft_putstr_fd(program[i], 1); //echo 다음 *char 출력
		if (program[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!endl)
		ft_putstr_fd("\n", 1); //-n 옵션이 없으면 endl == 0 이므로 개행 출력
}