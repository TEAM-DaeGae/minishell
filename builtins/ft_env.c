/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:05:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/29 02:29:44 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		write(STDOUT, envs[i], ft_strlen(envs[i]));
		write(STDOUT, "\n", 1);
		i++;
	}
	return (1);
}