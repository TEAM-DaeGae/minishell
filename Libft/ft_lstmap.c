/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:09:42 by gaekim            #+#    #+#             */
/*   Updated: 2020/04/18 19:32:44 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *lst_curr;
	t_list *new_curr;

	if (lst == NULL || f == NULL)
		return (NULL);
	if ((new = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	new_curr = new;
	lst_curr = lst->next;
	while (lst_curr != NULL)
	{
		if ((new_curr->next = ft_lstnew(f(lst_curr->content))) == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		new_curr = new_curr->next;
		lst_curr = lst_curr->next;
	}
	return (new);
}
