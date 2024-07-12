/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:37:00 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/12 14:05:23 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	slen(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		length;
	long	newn;
	char	*str;

	length = slen(n);
	newn = (long)n;
	str = (char *)ft_malloc(sizeof(char) * length + 1, 1);
	if (str == NULL)
		return (NULL);
	if (newn < 0)
		newn *= -1;
	str[length] = '\0';
	while (length--)
	{
		str[length] = newn % 10 + '0';
		newn /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
