/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/12 22:44:08 by daelee           ###   ########.fr       */
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

int				exec_builtin(char **program)
{
    char        *builtin;
    
    builtin = program[0];
	if (!ft_strncmp(builtin, "cd", ft_strlen(builtin)))
		ft_cd(program, g_envp);
	else if (!ft_strncmp(builtin, "echo", ft_strlen(builtin)))
		ft_echo(program);
	else if (!ft_strncmp(builtin, "pwd", ft_strlen(builtin)))
	 	ft_pwd();
	else if (!ft_strncmp(builtin, "env", ft_strlen(builtin)))
		ft_env(g_envp);
	else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
		ft_export(program);
	else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)))
		ft_unset(program);
	else if (!ft_strncmp(builtin, "exit", ft_strlen(builtin)))
		ft_exit(program);
	else
	{
		free_double_arr(program);
		return (0);
	}
	free_double_arr(program); //얘가 문제!! 수정필요!!!
	g_exit_status = 0;
	return (1);
}

// void			exec_cmds(char **cmdline)
// {
//     exec_builtin(cmdline);
// }