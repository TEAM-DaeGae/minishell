/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:11:52 by daelee            #+#    #+#             */
/*   Updated: 2021/01/31 17:43:17 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_envp(char **envs)
{
	char **new;
	int i;

	i = 0;
	while (envs[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}

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

char		*find_path(char *cmdline, char **envs)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_value("PATH", envs);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmdline);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			//free_double_arr(paths);
			return (new_path);
		}
		free(new_path);
	}
	//free_double_arr(paths);
	return (ft_strdup(cmdline));
}