/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:00:19 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:34:45 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pwd(void)
{
	char	*pwd;
	int		ret;

	ret = EXIT_SUCCESS;
	pwd = getcwd(0, MAXSIZE);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_exit_status = 0;
}
