/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 16:56:56 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/18 16:19:46 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*p;

	if (lst == NULL || f == NULL)
		return ;
	p = lst;
	while (p != NULL)
	{
		f(p->content);
		p = p->next;
	}
}
