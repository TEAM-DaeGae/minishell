/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/08 19:06:29 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int				exec_builtin(char **cmdline)
{
    char        *builtin;
    
    builtin = cmdline[0];
	// if (!ft_strncmp(builtin, "cd", ft_strlen(builtin)))
	// 	cd(cmdline);
	//if (!ft_strncmp(builtin, "echo", ft_strlen(builtin)))
	// 	echo(cmdline);
	else if (!ft_strncmp(builtin, "pwd", ft_strlen(builtin)))
	 	pwd();
	else if (!ft_strncmp(builtin, "env", ft_strlen(builtin)))
		env(g_envp);
	// else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
	// 	export(data->program);
	// else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)))
	// 	unset(data->program);
	// else if (!ft_strncmp(builtin, "exit", ft_strlen(builtin)))
	// 	exit(data->program);
	else
	{
		free_double_arr(cmdline);
		return (0);
	}
	free_double_arr(cmdline);
	g_exit_status = 0;
	return (1);
}

// void			exec_cmds(char **cmdline)
// {
//     exec_builtin(cmdline);
// }