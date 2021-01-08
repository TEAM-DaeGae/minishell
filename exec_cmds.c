/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:25 by daelee            #+#    #+#             */
/*   Updated: 2021/01/08 11:02:52 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				exec_builtin(t_data data, t_list *envs)
{
    char        *builtin;
    
    builtin = data->program[0];
	if (!ft_strncmp(builtin, "cd", ft_strlen(builtin)))
		cd(data->program, envs);
	else if (!ft_strncmp(builtin, "echo", ft_strlen(builtin)))
		echo(data->program);
	else if (!ft_strncmp(builtin, "pwd", ft_strlen(builtin)))
		pwd();
	else if (!ft_strncmp(builtin, "env", ft_strlen(builtin)))
		env(data->program, envs);
	else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
		export(data->program, envs);
	else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)))
		unset(data->program, envs);
	else if (!ft_strncmp(builtin, "exit", ft_strlen(builtin)))
		exit(data->program);
	else
	{
		//free_double_arr(data);
		return (0);
	}
	//free_double_arr(data);
	//g_exit_value = 0;
	return (1);
}

void			exec_cmds(t_data data, t_list *envs)
{
    exec_builtin(data, envs);
}