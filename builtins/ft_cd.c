/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:56:00 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 14:08:36 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmdline, char **envs)
{
	char	*path;

	path = 0;
	if (cmdline[1] == NULL || ((ft_double_strlen(cmdline) == 2) && (cmdline[1][0] == '~')))
	{
		path = find_value("HOME", envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	else if (cmdline[1][0] == '$')
	{
		path = find_value(&cmdline[1][1], envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (chdir(cmdline[1]) == -1)
		ft_putendl_fd(strerror(errno), 2);
}