/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:15:33 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/22 09:15:43 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_strdupsize(char *str, size_t size)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = ft_calloc(size, sizeof(char));
	if (dup == 0)
		return (0);
	if (str == 0)
		return (dup);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

char	*ft_make_line(char *line, char *buffer)
{
	int		i;
	size_t	len;
	char	*temp;

	i = 0;
	len = ft_strlen(line);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		temp = ft_strdupsize(line, len + i + 2);
	else
		temp = ft_strdupsize(line, len + i + 1);
	if (temp == 0)
		return (free(line), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		temp[i + len] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		temp[i + len] = '\n';
	return (free(line), temp);
}

int	ft_read_to_buffer(char *buffer, int fd)
{
	int	byte_read;

	byte_read = read(fd, buffer, BUFFER_SIZE);
	buffer[byte_read] = 0;
	return (byte_read);
}

void	ft_update_buffer(char *buffer)
{
	int	i;
	int	npos;

	i = 0;
	npos = 0;
	while (buffer[npos] && buffer[npos] != '\n')
		npos++;
	if (buffer[npos] == 0)
	{
		buffer[0] = 0;
		return ;
	}
	while (buffer[i + npos + 1])
	{
		buffer[i] = buffer[i + npos + 1];
		i++;
	}
	buffer[i] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			byte_read;

	byte_read = BUFFER_SIZE;
	line = ft_calloc(1, 1);
	line = ft_make_line(line, buffer);
	if (line == 0)
		return (0);
	ft_update_buffer(buffer);
	while (ft_strchr(line, '\n') == 0 && byte_read == BUFFER_SIZE)
	{
		byte_read = ft_read_to_buffer(buffer, fd);
		line = ft_make_line(line, buffer);
		if (line == 0)
			return (0);
		ft_update_buffer(buffer);
	}
	if (line[0] == 0 || byte_read < 0)
	{
		free(line);
		return (0);
	}
	return (line);
}
