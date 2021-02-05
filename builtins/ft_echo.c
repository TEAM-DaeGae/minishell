/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 22:56:30 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		ft_echo_envv(t_cmd *cmd, char **envs, int i)
{
	char 	*value;
	value = find_value(&(cmd->cmdline[i][1]), envs);
	ft_putstr_fd(value, STDIN);
}

int 	check_option_n(char *token)
{
	int i;

	if (ft_strncmp(token, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (token[i])
	{
		if (token[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		 	ft_echo(t_cmd *cmd, char **envs)
{
	int 	i;
	int 	option_n;
	int 	res;

	option_n = 0;
	i = 1;
	res = 0;
	while (check_option_n(cmd->cmdline[i]))
	{
		option_n = 1;
		i++;
	}
	while (cmd->cmdline[i])
	{
		if (cmd->cmdline[i][0] == '\'')
			res = remove_char(cmd->cmdline[i], '\'');
		if (cmd->cmdline[i][0] == '$' && res != TRUE)
			ft_echo_envv(cmd, envs, i);
		else
			ft_putstr_fd(cmd->cmdline[i], STDOUT);
		if (cmd->cmdline[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT);
	return (g_exit_status = 0);
}