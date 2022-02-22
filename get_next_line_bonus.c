/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanaka < stanaka@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:18:05 by stanaka           #+#    #+#             */
/*   Updated: 2022/02/22 16:42:04 by stanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *mem);
char	*free_mem(char **mem);
char	*get_line(char *mem);
char	*get_remainder_line(char *mem);

char	*get_next_line(int fd)
{
	static char	*mem[ULIMIT_FILE_DESCRIPTORS];
	char		*line;

	if (fd < 0 || ULIMIT_FILE_DESCRIPTORS <= fd \
	|| BUFFER_SIZE <= 0 || INT_MAX < (size_t)BUFFER_SIZE)
		return (NULL);
	if (!mem[fd])
	{
		mem[fd] = ft_strndup("", 1);
		if (!mem[fd])
			return (NULL);
	}
	mem[fd] = read_file(fd, mem[fd]);
	if (!mem[fd])
		return (NULL);
	line = get_line(mem[fd]);
	if (!line)
		return (free_mem(&mem[fd]));
	mem[fd] = get_remainder_line(mem[fd]);
	if (!mem[fd])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*read_file(int fd, char *mem)
{
	char		*buf;
	int			read_size;

	read_size = 1;
	while (!(ft_strchr(mem, '\n')) && read_size)
	{
		buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buf)
			return (free_mem(&mem));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buf);
			return (free_mem(&mem));
		}
		buf[read_size] = '\0';
		mem = ft_strjoin_free(mem, buf);
		if (!mem)
		{
			free(buf);
			return (NULL);
		}
	}
	return (mem);
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
	while (mem[i + len])
		len++;
	remainder_line = ft_strndup(&mem[i], len);
	free(mem);
	return (remainder_line);
}
