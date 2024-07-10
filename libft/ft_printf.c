/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:51:51 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:26:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	spesifier_check(const char *nformat, int *counter, va_list arg)
{
	if (!ft_strchr("cspdiuxX%", nformat[1]))
		ft_putchar(nformat[1], counter);
	else if (nformat[1] == 's')
		ft_putstr(va_arg(arg, const char *), counter);
	else if (nformat[1] == 'c')
		ft_putchar(va_arg(arg, int), counter);
	else if (nformat[1] == '%')
		ft_putchar('%', counter);
	else if (nformat[1] == 'd' || nformat[1] == 'i')
		ft_putnbr(va_arg(arg, int), counter);
	else if (nformat[1] == 'u')
		ft_putunbr(va_arg(arg, unsigned int), counter);
	else if (nformat[1] == 'x')
		ft_puthexa(va_arg(arg, int), counter, 0);
	else if (nformat[1] == 'X')
		ft_puthexa(va_arg(arg, int), counter, 1);
	else if (nformat[1] == 'p')
	{
		ft_putstr("0x", counter);
		ft_putaddress(va_arg(arg, unsigned long), counter);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	result = 0;
	va_start(args, format);
	if (write(1, "", 0) == -1)
		return (-1);
	while (*format)
	{
		if (*format == '%' && (*(format + 1)))
		{
			spesifier_check(format, &result, args);
			format += 2;
		}
		else if (*format == '%' && !(*(format + 1)))
			break ;
		else
		{
			ft_putchar(*format, &result);
			format++;
		}
	}
	va_end (args);
	return (result);
}
