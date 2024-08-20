/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:10:40 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/20 15:49:22 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(int signe)
{
	if (signe < 0)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int		signe;
	long	result;
	long	max_long;

	signe = 1;
	result = 0;
	max_long = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == 43 || *str == 45)
	{
		if (*str == 45)
			signe *= (-1);
		str++;
		break ;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + *str - '0';
		if (max_long > result)
			return (ft_check(signe));
		max_long = result;
		str++;
	}
	return (result * signe);
}
