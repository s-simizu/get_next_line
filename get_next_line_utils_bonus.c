/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimizu <sshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:15:52 by sshimizu          #+#    #+#             */
/*   Updated: 2023/02/11 11:19:08 by sshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **p)
{
	free(*p);
	*p = NULL;
	return (*p);
}

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

void	save_to_buffer(char *buffer, char *newline)
{
	size_t	len;

	len = ft_strlen(newline + 1);
	ft_memcpy(buffer, newline + 1, len);
	buffer[len] = '\0';
}
