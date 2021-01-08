/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:05:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/08 11:05:33 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_envs(t_list *envs)
{
	if (envs == NULL)
		return ;
	ft_putstr_fd(((t_env *)envs->content)->key, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(((t_env *)envs->content)->value, 1);
	print_envs(envs->next);
}

static char		*make_tmp_envs(char *tmp_envs, char *argv)
{
	char	*tmp;

	if (tmp_envs == NULL)
		tmp_envs = ft_strjoin(argv, "\n");
	else
	{
		tmp = ft_strjoin(argv, "\n");
		tmp_envs = ft_strjoin(tmp_envs, tmp);
		free(tmp);
	}
	return (tmp_envs);
}

void			env(char **argv, t_list *envs)
{
	char	*tmp_envs;

	tmp_envs = 0;
	argv++;
	while (*argv)
	{
		if (!is_valid_env(*argv))
		{
			ft_putstr_fd("env: ", 1);
			ft_putstr_fd(*argv, 1);
			ft_putendl_fd(": No such file or directory", 1);
			return ;
		}
		tmp_envs = make_tmp_envs(tmp_envs, *argv);
		argv++;
	}
	print_envs(envs);
	if (tmp_envs != NULL)
	{
		ft_putstr_fd(tmp_envs, 1);
		free(tmp_envs);
	}
}