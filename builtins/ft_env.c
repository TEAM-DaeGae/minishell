/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:05:25 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:38:50 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		write(STDOUT, envs[i], ft_strlen(envs[i]));
		write(STDOUT, "\n", 1);
		i++;
	}
	g_exit_status = 0;
}
