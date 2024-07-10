/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:18:11 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb, int *counter)
{
	if (nb == -2147483648)
	{
		*counter += write(1, "-2147483648", 11);
	}
	else if (nb < 0)
	{
		*counter += write(1, "-", 1);
		nb = -nb;
		ft_putnbr(nb, counter);
	}
	else if (nb >= 0 && nb <= 9)
	{
		nb += '0';
		*counter += write(1, &nb, 1);
	}
	else
	{
		ft_putnbr(nb / 10, counter);
		ft_putnbr(nb % 10, counter);
	}
}
