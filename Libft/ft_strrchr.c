/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:26:16 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/17 14:53:57 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if (result != 0)
		return (result);
	if (c == '\0')
		return ((char*)s);
	return (0);
}
