/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:44 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 16:20:04 by daelee           ###   ########.fr       */
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
		ft_putstr_fd(envs[i], STDIN);
		write(STDOUT, "\n", 1);
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

int 		ft_export(t_cmd *cmd)
{
	int     i;
	int     ret;

	i = 0;
	ret = 0;
	if (cmd->preflag == 1)
		return (1);
	if (ft_double_strlen(cmd->cmdline) == 1)
		ret = print_export(g_envp);
	else
	{
		while (cmd->cmdline[++i])
			ret = check_export(cmd->cmdline[i], &g_envp);
	}
	ret = g_exit_status;
	if (g_exit_status)
		return (1);
	else
		return (0);
}