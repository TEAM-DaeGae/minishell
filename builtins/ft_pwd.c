/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:00:19 by daelee            #+#    #+#             */
/*   Updated: 2021/02/04 14:10:56 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_pwd(void)
{
	char	*pwd;
	int 	ret;

	ret = EXIT_SUCCESS;
	pwd = getcwd(0, MAXSIZE);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (ret);
}