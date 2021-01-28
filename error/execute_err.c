/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:32:55 by daelee            #+#    #+#             */
/*   Updated: 2021/01/29 02:25:49 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     print_execute_err(char *token, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd(": ", STDERR);
    ft_putendl_fd(err_msg, STDERR);
	return (ERROR);
}