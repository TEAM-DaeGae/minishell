/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:37:53 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/21 18:13:00 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*p1;
	char	*p2;
	size_t	i;
	size_t	j;

	if (dest == 0 && src == 0)
		return (NULL);
	p1 = (char *)dest;
	p2 = (char *)src;
	i = 1;
	j = -1;
	if (p1 > p2)
	{
		while (i <= len)
		{
			p1[len - i] = p2[len - i];
			i++;
		}
	}
	else
	{
		while (++j < len)
			p1[j] = p2[j];
	}
	return (dest);
}
