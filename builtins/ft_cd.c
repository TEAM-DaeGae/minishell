/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:56:00 by daelee            #+#    #+#             */
/*   Updated: 2021/01/13 19:11:40 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_value(char *key, char **envs)
{
	int		i;

	i = -1;
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], key, ft_strlen(key)))
			return(envs[i] + ft_strlen(key) + 1);
	}
	return ("");
}

void	ft_cd(char **program, char **envs)
{
	char	*path;

	path = 0;
	if (program[1] == NULL || ((ft_double_strlen(program) == 2) && (program[1][0] == '~')))
	{
		path = find_value("HOME", envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	else if (program[1][0] == '$')
	{
		path = find_value(&program[1][1], envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (chdir(program[1]) == -1)
		ft_putendl_fd(strerror(errno), 2);
}