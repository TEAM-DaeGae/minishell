/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 20:21:56 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/21 18:11:26 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (dest == 0 && src == 0)
		return (NULL);
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	while (n > 0)
	{
		*p1 = *p2;
		p1++;
		p2++;
		n--;
	}
	return (dest);
}
