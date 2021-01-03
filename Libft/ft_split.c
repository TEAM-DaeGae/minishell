/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:22:46 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/20 23:17:53 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	each_len(char const *s, char c, int start)
{
	int		len;

	len = 0;
	while (s[start + len] != '\0' && s[start + len] != c)
		len++;
	return (len);
}

static int	find_start(char const *s, char c, int i)
{
	while (s[i] != '\0' && s[i] == c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == '\0' && s[i - 1] != c)
			count = count + 1;
		if (s[i] == '\0')
			break ;
		count++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	char	**array;
	int		start;
	int		i;
	int		j;

	i = 0;
	if (!(array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (NULL);
	start = find_start(s, c, 0);
	while (i < count_words(s, c))
	{
		j = 0;
		if (!(array[i] = malloc((each_len(s, c, start) + 1) * sizeof(char))))
			return (NULL);
		while (s[start + j] && s[start + j] != c)
		{
			array[i][j] = s[start + j];
			j++;
		}
		array[i][j] = '\0';
		start = find_start(s, c, start + j);
		i++;
	}
	array[i] = (char *)0;
	return (array);
}
