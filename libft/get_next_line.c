/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:16:12 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/10 20:25:19 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchr(char *s, int c)
{
	size_t	counter;

	counter = 0;
	while (counter <= ft_strlen(s))
	{
		if (s[counter] == (char)c)
			return ((char *)&s[counter]);
		counter++;
	}
	return (NULL);
}

static char	*buffer_update(char *buffer)
{
	char	*updated;
	int		start;

	start = 0;
	while (buffer[start] != '\n' && buffer[start])
		start++;
	if (buffer[start] == '\n')
		start++;
	else if (buffer[start] == '\0')
		return (free(buffer), NULL);
	updated = ft_substr(buffer, start, ft_strlen(buffer) - start);
	free(buffer);
	return (updated);
}

static char	*cut_nl(char *buffer)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[len] != '\n' && buffer[len])
		len++;
	if (buffer[len] == '\n')
		len++;
	line = ft_substr(buffer, 0, len);
	return (line);
}

static char	*read_lines(int fd, char *buffer)
{
	int		r_value;
	char	*read_buffer;

	read_buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (NULL);
	while (1)
	{
		r_value = read(fd, read_buffer, BUFFER_SIZE);
		if (r_value == -1)
		{
			free(buffer);
			free(read_buffer);
			return (NULL);
		}
		else if (r_value == 0)
			break ;
		read_buffer[r_value] = '\0';
		buffer = ft_strjoin(buffer, read_buffer);
		if (ft_strchr(read_buffer, '\n') != NULL)
			break ;
	}
	free(read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = read_lines(fd, buffer);
	if (!buffer)
		return (NULL);
	line = cut_nl(buffer);
	buffer = buffer_update(buffer);
	return (line);
}
