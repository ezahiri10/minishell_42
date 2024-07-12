/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:44:07 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/12 14:23:50 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		slen;
	int		counter;
	char	*nstr;

	counter = 0;
	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	nstr = (char *)ft_malloc(sizeof(char) * (slen + 1), 1);
	if (!nstr)
		return (NULL);
	while (s[counter])
	{
		nstr[counter] = f(counter, s[counter]);
		counter++;
	}
	nstr[counter] = '\0';
	return (nstr);
}
