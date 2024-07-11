/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:22:59 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/11 21:37:33 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
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
	substr = (char *)malloc((len + 1) * sizeof(char));//70
	if (substr == NULL)
		return (NULL);
	// printf ("-->%d\n", start);
	// printf ("-->%zu\n", len);
	while (counter < len && s)
	{
		substr[counter] = s[start + counter];
		// sleep(2);
		// printf ("%c---> %zu-->AScii %d\n", substr[counter], counter, substr[counter]);
		counter++;
	}
	substr[counter] = '\0';
	// sleep(2);
	return (substr);
}
