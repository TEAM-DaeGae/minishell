/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:27:56 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/18 19:24:20 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p;

	if (!(p = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}
