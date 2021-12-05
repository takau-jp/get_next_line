/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanaka < stanaka@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:54:16 by stanaka           #+#    #+#             */
/*   Updated: 2021/12/05 15:46:57 by stanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *mem);
char	*get_remainder_line(char *mem);

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*buf;
	int			read_size;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_size = 1;
	while (!(ft_strchr(mem, '\n')) && !read_size)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_size] = '\0';
		mem = ft_strjoin_free(mem, buf);
	}
	free(buf);
	line = get_line(mem);
	return (line);
}

char	*get_line(char *mem)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (!mem[i] && mem[i] != '\n')
		i++;
	if (mem[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = mem[j];
		j++;
	}
	line[j] = '\0';
	mem = get_remainder_line(&mem[j]);
	return (line);
}

char	*get_remainder_line(char *mem)
{
	char	*remainder_line;
	size_t	i;
	size_t	j;

	i = 0;
	if (mem[i] == '\n')
		i++;
	while (!mem[i])
		i++;
	remainder_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!remainder_line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		remainder_line[j] = mem[j];
		j++;
	}
	remainder_line[j] = '\0';
	free(mem);
	return (remainder_line);
}
