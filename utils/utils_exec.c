/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:11:52 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 13:51:45 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern 	char **g_envp;
extern 	int  g_exit_status;
char    **program;

void	free_double_arr(char **arr)
{
	int		idx;

	if (!arr)
		return ;
	idx = -1;
	while (arr[++idx])
		free(arr[idx]);
	free(arr);
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

char		*find_path(char *progam, char **envs)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_value("PATH", envs); // PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
	paths = ft_split(temp, ':'); //paths[0] == /usr/local/bin, paths[1] == /usr/bin, 
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", progam);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			free_double_arr(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_double_arr(paths);
	return (ft_strdup(progam));
}