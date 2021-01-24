/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:44 by daelee            #+#    #+#             */
/*   Updated: 2021/01/24 21:46:35 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_envp;

int	        print_export(char **envs)
{
	int	    i;

	i = -1;
	while (envs[++i])
	{
		ft_putstr_fd(envs[i], STDIN_FILENO);
		write(1, "\n", 1);
	}
	return (SUCCESS);
}

void        add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int	        check_export(char *str, char ***envs)
{
	int		i;
	char	**new;

	if (str[0] == '=' || str[0] == '\0' || ft_strlen(str) == 1)
		return (ERROR);
	i = -1;
	while ((*envs)[++i] != NULL)
		if (!ft_strncmp((*envs)[i], str, ft_strlen(str)))
		{
			free((*envs)[i]);
			(*envs)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (ERROR);
	i = -1;
	while ((*envs)[++i])
	{
		new[i] = ft_strdup((*envs)[i]);
		free((*envs)[i]);
	}
	add_export(str, new, i);
	free(*envs);
	*envs = new;
	return (SUCCESS);
}

int		    ft_export(char **cmdline)
{
	int     i;
	int     res;

	i = 0;
	res = 1;
	if (ft_double_strlen(cmdline) == 1)
		res = print_export(g_envp);
	else
	{
		while (cmdline[++i])
		{
			if (check_export(cmdline[i], &g_envp))
				;
			else
				res = 0;
		}
	}
	if (res)
		return (1);
	else
		return (0);
}