/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:22:58 by daelee            #+#    #+#             */
/*   Updated: 2021/02/05 01:23:33 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtin(char **cmdline)
{
    char *builtin;

    builtin = cmdline[0];
    if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo") \
    || !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env") \
    || !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export") \
    || !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit")) \
        return (TRUE);
    return (FALSE);
}