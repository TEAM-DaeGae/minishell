/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:44 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:39:13 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_export(char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		ft_putstr_fd(envs[i], STDIN);
		write(STDOUT, "\n", 1);
	}
}

void		add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int			check_export(char *str, char ***envs)
{
	int		i;
	char	**new;

	if (str[0] == '=' || str[0] == '\0' || ft_strlen(str) == 1)
		return (ERROR);
	i = -1;
	while ((*envs)[++i] != NULL)
		if (!ft_strncmp((*envs)[i], str, ft_strlen(str)))
		{
			(*envs)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (ERROR);
	i = -1;
	while ((*envs)[++i])
		new[i] = ft_strdup((*envs)[i]);
	add_export(str, new, i);
	*envs = new;
	return (SUCCESS);
}

int			isvalid_export(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if (key[i] >= '0' && key[i] <= '9')
			return (FALSE);
	}
	return (TRUE);
}

void		ft_export(t_cmd *cmd, char **cmdline)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	if (cmd->preflag == 1)
		return ;
	if (ft_double_strlen(cmdline) == 1)
		print_export(g_envp);
	else
	{
		remove_char(cmdline[1], '\'');
		while (cmdline[++i])
		{
			if (isvalid_export(ft_strtok(cmdline[i], '=')) == FALSE)
			{
				print_identifier_err("export", cmdline[i]);
				g_exit_status = 1;
			}
			ret = check_export(cmdline[i], &g_envp);
		}
	}
	if (ret != SUCCESS)
		g_exit_status = 1;
}
