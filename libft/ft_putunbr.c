/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:47:53 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr(unsigned int nb, int *counter)
{
	if (nb >= 0 && nb <= 9)
	{
		nb += '0';
		*counter += write(1, &nb, 1);
	}
	else
	{
		ft_putunbr(nb / 10, counter);
		ft_putunbr(nb % 10, counter);
	}
}
