/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:17:16 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexa(unsigned int decimal, int *counter, short boll)
{
	char	*hexadigit;

	hexadigit = "0123456789abcdef";
	if (boll == 1)
		hexadigit = "0123456789ABCDEF";
	if (decimal > 15)
	{
		ft_puthexa(decimal / 16, counter, boll);
		ft_putchar(hexadigit[decimal % 16], counter);
	}
	else
		ft_putchar(hexadigit[decimal], counter);
}
