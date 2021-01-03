/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 22:09:49 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/18 19:29:05 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = new;
	}
}
