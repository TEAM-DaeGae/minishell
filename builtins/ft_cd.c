/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:56:00 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 22:03:23 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd_home(char *path, char **envs)
{
	path = find_value("HOME", envs);
	if (chdir(path) == -1)
		print_execute_err_1("cd", "HOME not set");
	return (SUCCESS);
}

int 		ft_cd_envv(char *path, t_cmd *cmd, char **envs)
{
	path = find_value(&(cmd->cmdline[1][1]), envs);
	if (chdir(path) == -1)
		chdir(find_value("HOME", envs));
	return (SUCCESS);
}

int 		ft_cd(t_cmd *cmd, char **envs)
{
	char	*path;
	char	*cur_pwd;
	char	*old_pwd;
	char	*tmp;

	path = 0;
	if (cmd->cmdline[1] != NULL && cmd->cmdline[1][0] != '~' && cmd->cmdline[1][0] != '$')
	{
		path = cmd->cmdline[1];
		if (chdir(path) == -1)
			print_execute_err_2("cd", path, strerror(errno));
		if (!(tmp = malloc(sizeof(char) * MAXSIZE)))
			return (0);
		cur_pwd = ft_strjoin("PWD=", getcwd(tmp, MAXSIZE));
		old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", envs));
		check_export(cur_pwd, &envs);
		check_export(old_pwd, &envs);
		free(cur_pwd);
		free(old_pwd);
	}
	else if (cmd->cmdline[1] == NULL || cmd->cmdline[1][0] == '~')
		ft_cd_home(path, envs);
	else if (cmd->cmdline[1][0] == '$')
		ft_cd_envv(path, cmd, envs);
	return (SUCCESS);
}