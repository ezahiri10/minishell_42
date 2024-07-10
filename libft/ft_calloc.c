/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:28:38 by alafdili          #+#    #+#             */
/*   Updated: 2023/12/01 14:06:28 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	tsize;

	ptr = NULL;
	tsize = count * size;
	if (size > 0 && tsize / size != count)
		return (NULL);
	ptr = malloc(tsize);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, tsize);
	return (ptr);
}
