/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 07:19:21 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/08 00:41:22 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_single_redir(char *command, int i)
{
	if (command[i] == '>' && command[i - 1] != '>' && command[i + 1] != '>')
		return (1);
	return (0);
}

int		find_redir_type(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '>')
		return (DREDIR);
	else if (is_single_redir(command, i))
		return (REDIR);
	return (BREDIR);
}

int		has_redir_syntax_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" \n", str[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

char	*substr_and_trim(char *command, int start, int num, char *charset)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(command, start, num);
	temp2 = ft_strtrim(temp, charset);
	free(temp);
	return (temp2);
}

void	free_double_arr(char **arr)
{
	int		idx;

	if (!arr)
		return ;
	idx = -1;
	while (arr[++idx])
		free(arr[idx]);
	free(arr);
}
