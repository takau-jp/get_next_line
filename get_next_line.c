/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanaka < stanaka@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:54:16 by stanaka           #+#    #+#             */
/*   Updated: 2021/12/09 02:16:47 by stanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

bool	read_file(int fd, char **mem);
char	*free_mem(char **mem);
char	*get_line(char *mem);
char	*get_remainder_line(char *mem);

char	*get_next_line(int fd)
{
	static char	*mem = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (free_mem(&mem));
	if (!mem)
	{
		mem = ft_strndup("", 1);
		if (!mem)
			return (NULL);
	}
	if (!read_file(fd, &mem))
		return (free_mem(&mem));
	line = get_line(mem);
	if (!line)
		return (free_mem(&mem));
	mem = get_remainder_line(mem);
	if (!mem)
		return (NULL);
	return (line);
}

bool	read_file(int fd, char **mem)
{
	char		*buf;
	int			read_size;

	read_size = 1;
	while (!(ft_strchr(*mem, '\n')) && read_size)
	{
		buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buf)
			return (false);
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buf);
			return (false);
		}
		buf[read_size] = '\0';
		*mem = ft_strjoin_free(*mem, buf);
		if (!*mem)
		{
			free(buf);
			return (false);
		}
	}
	return (true);
}

char	*free_mem(char **mem)
{
	free(*mem);
	*mem = NULL;
	return (NULL);
}

char	*get_line(char *mem)
{
	char	*line;
	size_t	i;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	if (mem[i] == '\n')
		i++;
	if (i == 0)
		return (NULL);
	line = ft_strndup(mem, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_remainder_line(char *mem)
{
	char	*remainder_line;
	size_t	len;
	size_t	i;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	if (mem[i] == '\n')
		i++;
	len = 0;
	while (mem[len])
		len++;
	remainder_line = ft_strndup(&mem[i], len);
	free(mem);
	return (remainder_line);
}
