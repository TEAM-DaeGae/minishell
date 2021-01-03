/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 00:00:15 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/17 14:36:49 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	if (n > 0)
	{
		while (i + 1 < n)
		{
			if (p1[i] == p2[i])
				i++;
			else
				return (p1[i] - p2[i]);
		}
	}
	return (p1[i] - p2[i]);
}
