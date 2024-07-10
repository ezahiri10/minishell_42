/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:45:14 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/27 17:03:54 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c1;
	size_t	c2;

	c1 = 0;
	if (!haystack && !len)
		return (NULL);
	else if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[c1] && c1 < len)
	{
		c2 = 0;
		while (haystack[c1 + c2] == needle[c2] && c1 + c2 < len)
		{
			if (needle[c2 + 1] == '\0')
				return ((char *)&haystack[c1]);
			c2++;
		}
		c1++;
	}
	return (NULL);
}
