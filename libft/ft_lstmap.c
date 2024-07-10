/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:52:00 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/28 17:52:03 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new_lst = ft_lstnew(lst->content);
		if (!new_lst)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new_lst -> content = f(lst->content);
		ft_lstadd_back(&first, new_lst);
		lst = lst -> next;
	}
	return (first);
}
