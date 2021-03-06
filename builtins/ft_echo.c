/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/02/09 14:44:37 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_exit_status(void)
{
	ft_putstr_fd(ft_itoa(g_exit_status), 1);
}

void		ft_echo_envv(char **cmdline, char **envs, int i)
{
	char	*value;
	if (cmdline[1][0] == '$' && cmdline[1][1] == '?')
		print_exit_status();
	value = find_value(&(cmdline[i][1]), envs);
	ft_putstr_fd(value, STDIN);
}

int			check_option_n(char *token)
{
	int	i;

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

void		ft_echo(char **cmdline, char **envs)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (check_option_n(cmdline[i]))
	{
		ret = -1;
		i++;
	}
	while (cmdline[i])
	{
		if (cmdline[i][0] == '\'')
			ret = remove_char(cmdline[i], '\'');
		if (cmdline[i][0] == '$' && ret != TRUE)
			ft_echo_envv(cmdline, envs, i);
		else
			ft_putstr_fd(cmdline[i], STDOUT);
		if (cmdline[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (ret != -1)
		ft_putchar_fd('\n', STDOUT);
}
