/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:55:09 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(const char *str, int *counter)
{
	int	index;

	index = 0;
	if (!str)
	{
		*counter += write(1, "(null)", 6);
		return ;
	}
	while (str[index])
	{
		*counter += write(1, &str[index], 1);
		index++;
	}
}
