/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:12:47 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 00:49:41 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isvalid_env(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
		if (ft_isalnum(name[i]) || name[i] == '_')
			;
		else
			return (FALSE);
	if (!i)
		return (FALSE);
	return (TRUE);
}

int		check_key_value(char *str, char *envs)
{
	int	i;

	i = 0;
	while (str[i] && envs[i] && (str[i] == envs[i]) && (envs[i] != '='))
		i++;
	if ((str[i] == '\0') && (envs[i] == '='))
		return (TRUE);
	return (FALSE);
}

int		unset_env(char *str, char ***envs)
{
	int	i;
	int	last;

	last = 0;
	while (((*envs)[last]) != NULL)
		last++;
	if (last < 1)
		return (ERROR);
	i = -1;
	while ((*envs)[++i] != NULL)
		if (check_key_value(str, (*envs)[i]))
		{
			free((*envs)[i]);
			(*envs)[i] = ft_strdup((*envs)[last - 1]);
			free((*envs)[last - 1]);
			(*envs)[last - 1] = NULL;
			return (SUCCESS);
		}
	return (SUCCESS);
}

void	ft_unset(t_cmd *cmd, char **cmdline)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (cmd->preflag == 1)
		return ;
	while (cmdline[++i])
	{
		remove_char(cmdline[i], '\'');
		ret = isvalid_env(cmdline[i]) && unset_env(cmdline[i], &g_envp);
	}
	if (ret != 1)
		g_exit_status = 1;
}
