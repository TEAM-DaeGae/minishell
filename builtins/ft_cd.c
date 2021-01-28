/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:56:00 by daelee            #+#    #+#             */
/*   Updated: 2021/01/29 01:16:26 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd(char **cmdline, char **envs)
{
	char	*path;
	char	*cur_pwd;
	char	*old_pwd;
	char	*tmp;

	path = 0;
	if (cmdline[1][0] != '~' && cmdline[1][0] != '$')
	{
		path = cmdline[1];
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		if (!(tmp = malloc(sizeof(char) * MAXSIZE)))
			return (0);
		cur_pwd = ft_strjoin("PWD=", getcwd(tmp, MAXSIZE));
		old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", envs));
		check_export(cur_pwd, &envs);
		check_export(old_pwd, &envs);
		free(cur_pwd);
		free(old_pwd);
	}
	else if (cmdline[1] == NULL || ((ft_double_strlen(cmdline) == 2) && (cmdline[1][0] == '~')))
	{
		path = find_value("HOME", envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return (ERROR);
	}
	else if (cmdline[1][0] == '$')
	{
		path = find_value(&cmdline[1][1], envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return (ERROR);
	}
	return (SUCCESS);
}