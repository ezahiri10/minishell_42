/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:15:46 by alafdili          #+#    #+#             */
/*   Updated: 2023/11/26 10:06:49 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		counter;

	counter = ft_strlen(s);
	while (counter >= 0)
	{
		if (s[counter] == (char)c)
		{
			return ((char *) &s[counter]);
		}
		counter--;
	}
	return (NULL);
}
