/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:01:49 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/25 16:41:18 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ndst;
	unsigned char	*nsrc;

	if (src == NULL && dst == NULL)
		return (NULL);
	ndst = (unsigned char *)dst;
	nsrc = (unsigned char *)src;
	if (ndst > nsrc)
	{
		while (len--)
			ndst[len] = nsrc[len];
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
