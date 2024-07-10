/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:49 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/27 17:52:19 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	tlen;
	size_t	counter;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	counter = 0;
	tlen = 0;
	if (dstsize <= dlen)
		tlen += slen + dstsize;
	else
		tlen += slen + dlen;
	while (src[counter] && (dlen + 1) < dstsize)
	{
		dst[dlen] = src[counter];
		dlen++;
		counter++;
	}
	dst[dlen] = '\0';
	return (tlen);
}
