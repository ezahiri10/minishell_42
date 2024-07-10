/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:52:26 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/28 17:52:31 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ns;

	ns = (unsigned char *)s;
	while (n--)
	{
		if (*ns == (unsigned char)c)
			return (ns);
		ns++;
	}
	return (NULL);
}
