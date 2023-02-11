/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimizu <sshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:20:14 by sshimizu          #+#    #+#             */
/*   Updated: 2023/02/11 09:54:48 by sshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;
	size_t			i;

	b1 = (unsigned char *)buf1;
	b2 = (unsigned char *)buf2;
	i = 0;
	while (i < n)
	{
		b1[i] = b2[i];
		i++;
	}
	return ((void *)b1);
}

char	*ft_strchr(const char *s, int c)
{
	char	cc;
	size_t	len;
	size_t	i;

	cc = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == cc)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*buffer_flush(char *buffer)
{
	char	*block;
	size_t	len;

	len = ft_strlen(buffer);
	block = malloc(len + 1);
	if (!block)
		return (NULL);
	ft_memcpy(block, buffer, len);
	block[len] = '\0';
	buffer[0] = '\0';
	return (block);
}

char	*buffer_join(char *block, char *buffer, ssize_t rc)
{
	char	*new;
	size_t	new_len;
	size_t	block_len;

	block_len = ft_strlen(block);
	new_len = block_len + rc;
	new = malloc(new_len + 1);
	if (!new)
	{
		free(block);
		return (NULL);
	}
	ft_memcpy(new, block, block_len);
	ft_memcpy(new + block_len, buffer, rc);
	new[new_len] = '\0';
	free(block);
	return (new);
}

char	*read_block(int fd, char *buffer)
{
	char	*block;
	ssize_t	rc;

	block = buffer_flush(buffer);
	if (!block)
		return (NULL);
	rc = BUFFER_SIZE;
	while (!ft_strchr(block, '\n') && rc == BUFFER_SIZE)
	{
		rc = read(fd, buffer, BUFFER_SIZE);
		block = buffer_join(block, buffer, rc);
		if (!block)
			return (NULL);
	}
	if (rc < 0)
	{
		free(block);
		return (NULL);
	}
	buffer[0] = '\0';
	return (block);
}

void	save_to_buffer(char *buffer, char *newline)
{
	size_t	len;

	len = ft_strlen(newline + 1);
	ft_memcpy(buffer, newline + 1, len);
	buffer[len] = '\0';
}

char	*get_line(char *block, char *buffer)
{
	char	*line;
	char	*newline;
	size_t	line_len;

	newline = ft_strchr(block, '\n');
	if (!newline)
		return (block);
	line_len = newline - block + 1;
	line = malloc(line_len + 1);
	if (!line)
	{
		free(block);
		return (NULL);
	}
	ft_memcpy(line, block, line_len);
	line[line_len] = '\0';
	save_to_buffer(buffer, newline);
	free(block);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*block;
	char		*line;

	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	block = read_block(fd, buffer);
	if (!block)
		return (NULL);
	line = get_line(block, buffer);
	if (!line[0])
		return (NULL);
	return (line);
}
