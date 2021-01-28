/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:29:47 by daelee            #+#    #+#             */
/*   Updated: 2021/01/29 02:25:37 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errno_err(char *err_msg)
{
	ft_putstr_fd("Error : ", STDERR);
	ft_putstr_fd(err_msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(EXIT_FAILURE);
}
