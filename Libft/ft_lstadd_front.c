/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:50:40 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/16 22:21:28 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	else if (*lst == 0 && new != NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
