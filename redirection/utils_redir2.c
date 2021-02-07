/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 07:27:16 by gaekim            #+#    #+#             */
/*   Updated: 2021/02/08 00:41:21 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_puterror_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

char	*ft_strjoin_c(char *s, char c)
{
	char	*p;
	int		i;

	i = 0;
	p = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = c;
	p[i + 1] = '\0';
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (p);
}

char	*change_from_double_to_single_cmdline(char **cmdline)
{
	char	*new_line;
	char	*temp;
	int		i;

	if (!cmdline)
		return (NULL);
	new_line = ft_strdup("");
	i = 0;
	while (cmdline[i])
	{
		temp = ft_strjoin(new_line, cmdline[i]);
		free(new_line);
		new_line = temp;
		if (cmdline[i + 1] != NULL)
			new_line = ft_strjoin_c(new_line, ' ');
		i++;
	}
	new_line[ft_strlen(new_line)] = '\0';
	return (new_line);
}

char	*remove_single_quotes(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			p[i] = ' ';
		else
			p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (p);
}
