/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:11 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/12 14:44:05 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	counter;
	size_t len;

	if (!s)
		return (NULL);
	counter = 0;
	len = ft_strlen(s);
	while (counter <= len)
	{
		if (s[counter] == (char)c)
		{
			return ((char *)&s[counter]);
		}
		counter++;
	}
	return (NULL);
}
