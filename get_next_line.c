/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimizu <sshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:20:14 by sshimizu          #+#    #+#             */
/*   Updated: 2023/02/12 05:24:30 by sshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		return (ft_free(&block));
	ft_memcpy(new, block, block_len);
	ft_memcpy(new + block_len, buffer, rc);
	new[new_len] = '\0';
	buffer[0] = '\0';
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
	while (rc == BUFFER_SIZE && !ft_strchr(block, '\n'))
	{
		rc = read(fd, buffer, BUFFER_SIZE);
		if (rc < 0)
			return (ft_free(&block));
		block = buffer_join(block, buffer, rc);
		if (!block)
			return (NULL);
	}
	if (block[0] == '\0')
		ft_free(&block);
	return (block);
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
		return (ft_free(&block));
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

	if (fd < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	block = read_block(fd, buffer);
	if (!block)
		return (ft_free(&buffer));
	line = get_line(block, buffer);
	if (!line)
		ft_free(&buffer);
	return (line);
}
