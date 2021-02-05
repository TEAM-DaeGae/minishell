/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:12:47 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 16:34:16 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_envp;

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

int			check_key_value(char *str, char *envs)
{
	int		i;

	i = 0;
	while (str[i] && envs[i] && (str[i] == envs[i]) && (envs[i] != '='))
		i++;
	if ((str[i] == '\0') && (envs[i] == '='))
		return (TRUE);
	return (FALSE);
}

int			unset_env(char *str, char ***envs)
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

int 	ft_unset(t_cmd *cmd)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (cmd->preflag == 1)
		return (1);
	while (cmd->cmdline[++i])
		ret = isvalid_env(cmd->cmdline[i]) && unset_env(cmd->cmdline[i], &g_envp);
	ret = g_exit_status;
	if (g_exit_status)
		return (1);
	else
		return (0);
}