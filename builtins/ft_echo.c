/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/02/06 20:43:51 by daelee           ###   ########.fr       */
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

void ft_echo(t_cmd *cmd, char **envs)
{
	int 	i;
	int 	ret;

	i = 1;
	ret = 0;
	while (check_option_n(cmd->cmdline[i]))
	{
		ret = -1;
		i++;
	}
	while (cmd->cmdline[i])
	{
		if (cmd->cmdline[i][0] == '\'')
			ret = remove_char(cmd->cmdline[i], '\'');
		if (cmd->cmdline[i][0] == '$' && ret != TRUE)
			ft_echo_envv(cmd, envs, i);
		else
			ft_putstr_fd(cmd->cmdline[i], STDOUT);
		if (cmd->cmdline[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (ret != -1)
		ft_putchar_fd('\n', STDOUT);
}