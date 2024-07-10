/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:31:43 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/29 16:59:30 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ndst;
	size_t			counter;

	ndst = dst;
	counter = 0;
	while (counter < n && dst != src)
	{
		ndst[counter] = ((unsigned char *)src)[counter];
		counter++;
	}
	return (dst);
}
