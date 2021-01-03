/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 20:43:13 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/07 20:56:31 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(size * count);
	if (p == NULL)
		return (NULL);
	while (i < size * count)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
