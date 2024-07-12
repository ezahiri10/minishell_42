/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:22:59 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/12 14:30:47 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	counter;

	if (!s)
		return (NULL);
	counter = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = ft_malloc((len + 1) * sizeof(char), 1);
	if (!substr)
		return (NULL);
	while (counter < len && s)
	{
		substr[counter] = s[start + counter];
		counter++;
	}
	substr[counter] = '\0';
	return (substr);
}
