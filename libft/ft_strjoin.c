/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:29:43 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/24 19:09:12 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*constr;
	int		flen;
	int		slen;

	if (!s1 && !s2)	
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	flen = ft_strlen(s1);
	slen = ft_strlen(s2);
	constr = (char *) ft_malloc((flen + slen + 1) * sizeof(char), 1);
	if (constr == NULL)
		return (NULL);
	ft_strlcpy (constr, s1, flen + 1);
	ft_strlcat (constr, s2, (flen + slen + 1));
	return (constr);
}
