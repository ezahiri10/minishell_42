/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:22:48 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/18 21:49:56 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	stock_addr(void *addr, int mode)
{
	static t_list	*buffer;
	static void		*tmp;
	t_list			*new;

	if (mode == 1)
	{
		new = ft_lstnew(addr);
		if (!new)
			handle_error(addr);
		ft_lstadd_back(&buffer, new);
	}
	else if (mode == 2)
	{
		free(tmp);
		tmp = addr;
	}
	else
	{
		free(tmp);
		ft_lstclear(&buffer, free);
	}
}
