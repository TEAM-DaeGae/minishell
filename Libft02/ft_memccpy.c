/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:41:26 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/21 18:10:36 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	while (p2[i] != (unsigned char)c && i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	if (p2[i] == (unsigned char)c)
	{
		p1[i] = p2[i];
		return ((void *)(dest + i + 1));
	}
	return (NULL);
}
