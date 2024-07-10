/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:12:48 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/27 15:22:23 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*ptr;
	size_t				counter;

	ptr = b;
	counter = 0;
	while (counter < len)
	{
		ptr[counter] = (unsigned char)c;
		counter++;
	}
	return (ptr);
}
