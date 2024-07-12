/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:39:16 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/12 14:18:41 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		counter;
	int		slen;

	slen = ft_strlen(s1);
	counter = 0;
	str = (char *)ft_malloc(slen * sizeof(char) + 1, 1);
	if (str == NULL)
		return (NULL);
	while (counter < slen)
	{
		str[counter] = s1[counter];
		counter++;
	}
	str[counter] = '\0';
	return (str);
}
