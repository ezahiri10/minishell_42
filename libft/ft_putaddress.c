/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:43:37 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddress(unsigned long decimal, int *counter)
{
	char	*hexadigit;

	hexadigit = "0123456789abcdef";
	if (decimal > 15)
	{
		ft_putaddress(decimal / 16, counter);
		ft_putchar(hexadigit[decimal % 16], counter);
	}
	else
		ft_putchar(hexadigit[decimal], counter);
}
