/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:32:55 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:34:45 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_execute_err_1(char *token, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (ERROR);
}

int		print_execute_err_2(char *token1, char *token2, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token1, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token2, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (ERROR);
}
