/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:27:28 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/18 16:01:34 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_error(char *str, void *to_free)
{
	free(to_free);
	ft_malloc(0, 0);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	*ft_malloc(size_t size, int mod)
{
	static t_list	*head;
	void			*ptr;
	t_list			*new;

	ptr = NULL;
	if (mod == 1)
	{
		ptr = malloc(size);
		if (!ptr)
			handle_error("Malloc failed\n", ptr);
		new = ft_lstnew(ptr);
		if (!new)
			handle_error("Malloc failed\n", ptr);
		ft_lstadd_back(&head, new);
		return (ptr);
	}
	else
		ft_lstclear(&head, free);
	return (NULL);
}
